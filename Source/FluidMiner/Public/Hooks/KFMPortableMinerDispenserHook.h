#pragma once

#include "CoreMinimal.h"
#include "Patching/NativeHookManager.h"
#include "UObject/NoExportTypes.h"
#include "KFMPortableMinerDispenserHook.generated.h"

class AFGPortableMinerDispenser;
class AFGResourceNode;

/**
 * Hook into portable miner dispenser to disallow placement of portable miners on fluid mining resource nodes.
 */
UCLASS()
class FLUIDMINER_API UKFMPortableMinerDispenserHook : public UObject
{
	GENERATED_BODY()

public:
	static void IsResourceNodeValid(TCallScope<bool(*)(const AFGPortableMinerDispenser*, const AFGResourceNode*)>& Scope, const AFGPortableMinerDispenser* Self, const AFGResourceNode* ResourceNode);
	static void Server_SpawnPortableMiner(TCallScope<void(*)(AFGPortableMinerDispenser*, const FVector&, AFGResourceNode*)>& Scope, AFGPortableMinerDispenser* Self, const FVector& Locations, AFGResourceNode* ResourceNode);
};
