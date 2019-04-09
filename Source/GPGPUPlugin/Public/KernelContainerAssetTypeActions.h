#pragma once

#include "CoreMinimal.h"

#include "Developer/AssetTools/Public/AssetTypeActions_Base.h" // FAssetTypeActions_Base
#include "Developer/AssetTools/Public/AssetTypeCategories.h" // EAssetTypeCategories::Type

class FMenuBuilder;

class FKernelContainerAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FKernelContainerAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
    virtual FColor GetTypeColor() const override;
    virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
private:
	EAssetTypeCategories::Type MyAssetCategory;
};
