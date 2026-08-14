#include "KhaosFluidOreExtractor.h"
#include "FGInventoryComponent.h"
#include "FGFactoryConnectionComponent.h"
#include "FGPipeConnectionComponent.h"
#include "KhaosFluidMiningResourceNode.h"

AKhaosFluidOreExtractor::AKhaosFluidOreExtractor()
{
	mInputInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("InputInventory"));
}

void AKhaosFluidOreExtractor::BeginPlay()
{
	AKhaosFluidMiningResourceNode* Node = Cast<AKhaosFluidMiningResourceNode>(GetExtractableResource().GetObject());
	if (!Node)
	{
		Super::BeginPlay();
		return;
	}

	mExtractCycleTime = Node->GetCycleTime() * mExtractCycleTime;
	mItemsPerCycle = Node->GetItemsPerCycle();
	mMiningFluidPerCycle = Node->GetMiningFluidPerCycle();
	mMiningFluidClass = Node->GetMiningFluidClass();

	mInputInventory->SetReplicationRelevancyOwner(this);
	mInputInventory->SetAllowedItemOnIndex(0, mMiningFluidClass);

	mOutputInventory->SetAllowedItemOnIndex(0, Node->GetResourceClass());
	mOutputInventory->RemoveArbitrarySlotSize(0);

	ForEachComponent<UFGFactoryConnectionComponent>(true, [&](UFGFactoryConnectionComponent* FactoryConnection) {
		switch (FactoryConnection->GetDirection()) {
		case EFactoryConnectionDirection::FCD_OUTPUT:
			mOutputInventoryConnection = FactoryConnection;
			mOutputInventoryConnection->SetInventory(mOutputInventory);
			mOutputInventoryConnection->SetInventoryAccessIndex(0);
			break;
		}
	});

	ForEachComponent<UFGPipeConnectionComponent>(true, [&](UFGPipeConnectionComponent* FactoryConnection) {
		switch (FactoryConnection->GetPipeConnectionType()) {
		case EPipeConnectionType::PCT_CONSUMER:
			mInputInventoryConnection = FactoryConnection;
			mInputInventoryConnection->SetInventoryAccessIndex(0);
			break;
		}
	});

	Super::BeginPlay();
}

bool AKhaosFluidOreExtractor::CanProduce_Implementation() const
{
	FInventoryStack OutputStack = FInventoryStack(mItemsPerCycle, GetExtractableResource()->GetResourceClass());

	return HasPower()
		&& !IsProductionPaused()
		&& GetInputInventory()->HasItems(mMiningFluidClass, mMiningFluidPerCycle)
		&& GetOutputInventory()->HasEnoughSpaceForStack(OutputStack);
}

void AKhaosFluidOreExtractor::Factory_Tick(float dt)
{
	Super::Factory_Tick(dt);

	if (!HasAuthority() || IsProductionPaused()) {
		return;
	}

	FInventoryStack InputFluid;
	const int32 Space = mInputInventory->GetSlotSize(0, mMiningFluidClass) - mInputInventory->GetNumItems(mMiningFluidClass);

	while (mInputInventory->HasEnoughSpaceForItem(FInventoryItem(mMiningFluidClass))
		&& mInputInventoryConnection->Factory_PullPipeInput(dt, InputFluid, mMiningFluidClass, Space)
		&& InputFluid.HasItems())
	{
		mInputInventory->AddStackToIndex(0, InputFluid);
	}
}

void AKhaosFluidOreExtractor::Factory_TickProducing(float dt)
{
	Super::Super::Factory_TickProducing(dt);

	if (!HasAuthority()) {
		return;
	}

	mCurrentExtractProgress += (1.f / CalcProductionCycleTimeForPotential(GetCurrentPotential())) * dt;
	if (mCurrentExtractProgress >= 1.f)
	{
		mInputInventory->RemoveFromIndex(0, mMiningFluidPerCycle);

		FInventoryStack OutputStack = FInventoryStack(mItemsPerCycle, GetExtractableResource()->GetResourceClass());
		mOutputInventory->AddStackToIndex(0, OutputStack);

		Factory_ProductionCycleCompleted(mCurrentExtractProgress - 1.f);
		mCurrentExtractProgress -= 1.f;
	}
}

float AKhaosFluidOreExtractor::GetMiningFluidConsumptionPerMinute() const
{
	const float CycleTime = GetProductionCycleTime();
	if (CycleTime > SMALL_NUMBER)
	{
		return (mMiningFluidPerCycle / CycleTime) * 60.f;
	}

	return 0.f;
}

float AKhaosFluidOreExtractor::GetExtractedItemsPerMinute() const
{
	const float CycleTime = GetProductionCycleTime();
	if (CycleTime > SMALL_NUMBER)
	{
		return (mItemsPerCycle / CycleTime) * 60.f;
	}

	return 0.f;
}
