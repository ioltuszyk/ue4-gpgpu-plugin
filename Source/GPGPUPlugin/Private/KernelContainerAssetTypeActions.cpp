#include "KernelContainerAssetTypeActions.h"

#include "KernelContainer.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

//////////////////////////////////////////////////////////////////////////
// FKernelContainerAssetTypeActions

FKernelContainerAssetTypeActions::FKernelContainerAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FKernelContainerAssetTypeActions::GetName() const
{
	return LOCTEXT("FKernelContainerAssetTypeActionsName", "Kernel Container");
}

FColor FKernelContainerAssetTypeActions::GetTypeColor() const
{
	return FColor::Purple;
}

UClass* FKernelContainerAssetTypeActions::GetSupportedClass() const
{
	return UKernelContainer::StaticClass();
}

uint32 FKernelContainerAssetTypeActions::GetCategories()
{
	return MyAssetCategory;
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
