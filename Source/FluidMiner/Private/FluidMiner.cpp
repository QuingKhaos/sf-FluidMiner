#include "FluidMiner.h"
#include "Equipment/FGPortableMinerDispenser.h"
#include "Hooks/KFMPortableMinerDispenserHook.h"
#include "Patching/NativeHookManager.h"

#define LOCTEXT_NAMESPACE "FFluidMinerModule"

void FFluidMinerModule::StartupModule()
{
	FCoreDelegates::OnPostEngineInit.AddLambda([]() {
		if (!WITH_EDITOR) {
			SUBSCRIBE_UOBJECT_METHOD(AFGPortableMinerDispenser, IsResourceNodeValid, &UKFMPortableMinerDispenserHook::IsResourceNodeValid);
			SUBSCRIBE_UOBJECT_METHOD(AFGPortableMinerDispenser, Server_SpawnPortableMiner, &UKFMPortableMinerDispenserHook::Server_SpawnPortableMiner);
		}
	});
}

void FFluidMinerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFluidMinerModule, FluidMiner)
