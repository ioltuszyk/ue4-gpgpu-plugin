#include "GPGPUPlugin.h"

#include "KernelContainerAssetTypeActions.h"

#define LOCTEXT_NAMESPACE "FGPGPUPluginModule"

//////////////////////////////////////////////////////////////////////////
// FGPGPUPluginModule

void FGPGPUPluginModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	GPGPUPluginCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("GPGPU")), LOCTEXT("GPGPUPluginCategory", "GPGPU"));
	
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FKernelContainerAssetTypeActions(GPGPUPluginCategoryBit)));
}

void FGPGPUPluginModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}
	CreatedAssetTypeActions.Empty();
}

bool FGPGPUPluginModule::SupportsDynamicReloading() 
{
	return true;
}

void FGPGPUPluginModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGPGPUPluginModule, GPGPUPlugin)