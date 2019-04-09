#pragma once

#include "CoreMinimal.h"

#include "UnrealEd.h" // UFactory

#include "KernelContainerFactory.generated.h"
 
UCLASS()
class UKernelContainerFactory : public UFactory
{
	GENERATED_BODY()
 
 public:
    UKernelContainerFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool ShouldShowInNewMenu() const override;
};