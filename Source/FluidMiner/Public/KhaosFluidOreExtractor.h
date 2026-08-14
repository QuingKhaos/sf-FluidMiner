#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableResourceExtractor.h"
#include "KhaosFluidOreExtractor.generated.h"

/**
 * A miner, that needs to be supplied with a mining fluid to mine a resource node.
 */
UCLASS()
class FLUIDMINER_API AKhaosFluidOreExtractor : public AFGBuildableResourceExtractor
{
	GENERATED_BODY()

public:
	AKhaosFluidOreExtractor();

    // Begin AActor interface

    virtual void BeginPlay() override;
    // End AActor interface

    //~ Begin FGBuildableFactory Interface
    virtual bool CanProduce_Implementation() const override;
    virtual void Factory_Tick(float dt) override;
    virtual void Factory_TickProducing(float dt) override;
    //~ End FGBuildableFactory Interface

    /** Get the input inventory where the mining fluid is stored */
    UFUNCTION(BlueprintPure, Category = "Fluid Miner")
    FORCEINLINE UFGInventoryComponent* GetInputInventory() const { return mInputInventory; }

    /** Get the required mining fluid class */
	UFUNCTION(BlueprintPure, Category = "Fluid Miner")
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetMiningFluidClass() const { return mMiningFluidClass; }

    /** The mining fluid consumed per cycle */
	UFUNCTION(BlueprintPure, Category = "Fluid Miner")
	FORCEINLINE float GetMiningFluidPerCycle() const { return mMiningFluidPerCycle; }

    /** Get the mining fluid consumption rate per minute converted for displaying in the UI */
    UFUNCTION(BlueprintPure, Category = "Fluid Miner")
    float GetMiningFluidConsumptionPerMinute() const;

    /** Get the quantity of items extracted per minute converted for displaying in the UI */
    UFUNCTION(BlueprintPure, Category = "Fluid Miner")
    float GetExtractedItemsPerMinute() const;

protected:
	UPROPERTY()
	TObjectPtr<UFGInventoryComponent> mInputInventory;

	UPROPERTY()
	TObjectPtr<UFGPipeConnectionComponent> mInputInventoryConnection;

	UPROPERTY()
	TObjectPtr<UFGFactoryConnectionComponent> mOutputInventoryConnection;

	UPROPERTY()
	TSubclassOf<UFGItemDescriptor> mMiningFluidClass;

	UPROPERTY()
	float mMiningFluidPerCycle;
};
