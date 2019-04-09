#pragma once

#include "CoreMinimal.h"

#include "Runtime/Core/Public/Modules/ModuleInterface.h" // IModuleInterface
#include "Developer/AssetTools/Public/IAssetTools.h" // IAssetTools
#include "Developer/AssetTools/Public/AssetTypeCategories.h" // EAssetTypeCategories::Type
#include "Developer/AssetTools/Public/IAssetTypeActions.h" // IAssetTypeActions

class FGPGPUPluginModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override;

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
protected:
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
	EAssetTypeCategories::Type GPGPUPluginCategoryBit;
};
