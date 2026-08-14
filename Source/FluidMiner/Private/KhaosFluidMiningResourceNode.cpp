#include "KhaosFluidMiningResourceNode.h"

void AKhaosFluidMiningResourceNode::BeginPlay()
{
	Super::BeginPlay();
}

void AKhaosFluidMiningResourceNode::UpdateUseState_Implementation(AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState)
{
	// Intentionally empty to prevent the player from mining the node directly.
}

void AKhaosFluidMiningResourceNode::OnUse_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state)
{
	// Intentionally empty to prevent the player from mining the node directly.
}

void AKhaosFluidMiningResourceNode::OnUseStop_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state)
{
	// Intentionally empty to prevent the player from mining the node directly.
}

void AKhaosFluidMiningResourceNode::StartIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state)
{
	// Intentionally empty to prevent the player from mining the node directly.
}

FText AKhaosFluidMiningResourceNode::GetLookAtDecription_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) const
{
	return FText::FormatNamed(FText::FromStringTable("/FluidMiner/ST_FluidMiner.ST_FluidMiner", TEXT("FluidMiningResourceNode/LookAtDesc/Pattern")),
		TEXT("Ore"), UFGItemDescriptor::GetItemName(GetResourceClass()),
		TEXT("Purity"), GetResourcePurityText(),
		TEXT("MiningFluid"), mMiningFluidClass ? UFGItemDescriptor::GetItemName(mMiningFluidClass) : FText::FromString(TEXT("None"))
	);
}

void AKhaosFluidMiningResourceNode::StopIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state)
{
	// Intentionally empty to prevent the player from mining the node directly.
}
