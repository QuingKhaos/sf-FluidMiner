#pragma once

#include "CoreMinimal.h"
#include "Engine/HitResult.h"
#include "Resources/FGResourceNode.h"
#include "KhaosFluidMiningResourceNode.generated.h"

/**
 * A resource node, which can only be mined by a miner that is supplied with a mining fluid.
 */
UCLASS()
class FLUIDMINER_API AKhaosFluidMiningResourceNode : public AFGResourceNode
{
	GENERATED_BODY()

public:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//~ Begin FGUseableInterface Interface
	virtual void UpdateUseState_Implementation(class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState) override;
	virtual void OnUse_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual void OnUseStop_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual void StartIsLookedAt_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual FText GetLookAtDecription_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state) const override;
	virtual void StopIsLookedAt_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	//~ End FGUseableInterface Interface

	UFUNCTION(BlueprintPure, Category = "Fluid Miner")
	FORCEINLINE TSubclassOf<class UFGItemDescriptor> GetMiningFluidClass() const { return mMiningFluidClass; }

	UFUNCTION(BlueprintPure, Category = "Fluid Miner")
	FORCEINLINE float GetCycleTime() const { return mCycleTime; }

	UFUNCTION(BlueprintPure, Category = "Fluid Miner")
	FORCEINLINE int32 GetItemsPerCycle() const { return mItemsPerCycle; }

	UFUNCTION(BlueprintPure, Category = "Fluid Miner")
	FORCEINLINE int32 GetMiningFluidPerCycle() const { return mMiningFluidPerCycle; }

protected:
	/** Mining fluid to be consumed */
	UPROPERTY(EditDefaultsOnly, Category = "Fluid Miner")
	TSubclassOf<class UFGItemDescriptor> mMiningFluidClass;

	/** Cycle time (for Mk.1 extractor, normal node quality) */
	UPROPERTY(EditDefaultsOnly, Category = "Fluid Miner")
	float mCycleTime;

	/** Production of output item per cycle */
	UPROPERTY(EditDefaultsOnly, Category = "Fluid Miner")
	int32 mItemsPerCycle;

	/** Consumption of mining fluid per cycle */
	UPROPERTY(EditDefaultsOnly, Category = "Fluid Miner")
	int32 mMiningFluidPerCycle;
};
