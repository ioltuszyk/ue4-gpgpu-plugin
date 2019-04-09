#include "KernelContainerFactory.h"
 
UKernelContainerFactory::UKernelContainerFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UKernelContainer::StaticClass();
}
 
UObject* UKernelContainerFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UKernelContainer* NewObjectAsset = NewObject<UKernelContainer>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

bool UKernelContainerFactory::ShouldShowInNewMenu() const
{
    return true;
}