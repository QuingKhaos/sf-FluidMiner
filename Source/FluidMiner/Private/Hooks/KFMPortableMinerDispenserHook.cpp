#include "Hooks/KFMPortableMinerDispenserHook.h"
#include "Templates/Function.h"
#include "Equipment/FGPortableMinerDispenser.h"
#include "Resources/FGResourceNode.h"
#include "KhaosFluidMiningResourceNode.h"

void UKFMPortableMinerDispenserHook::IsResourceNodeValid(TCallScope<bool(*)(const AFGPortableMinerDispenser*, const AFGResourceNode*)>& Scope, const AFGPortableMinerDispenser* Self, const AFGResourceNode* ResourceNode)
{
	if (ResourceNode->IsA(AKhaosFluidMiningResourceNode::StaticClass()))
	{
		Scope.Override(false);
	}
}

void UKFMPortableMinerDispenserHook::Server_SpawnPortableMiner(TCallScope<void(*)(AFGPortableMinerDispenser*, const FVector&, AFGResourceNode*)>& Scope, AFGPortableMinerDispenser* Self, const FVector& Locations, AFGResourceNode* ResourceNode)
{
	if (ResourceNode->IsA(AKhaosFluidMiningResourceNode::StaticClass()))
	{
		Scope.Cancel();
	}
}
