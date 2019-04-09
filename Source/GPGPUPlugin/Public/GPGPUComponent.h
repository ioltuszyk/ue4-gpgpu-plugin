#pragma once

#include "CoreMinimal.h"

#include "KernelContainer.h"
#include "UObject/ObjectMacros.h"
#include "GPGPUComponent.generated.h"

UCLASS(ClassGroup = "GPGPU", DisplayName = "GPGPU Component", HideCategories = (Tags), meta = (BlueprintSpawnableComponent))
class UGPGPUComponent : public UActorComponent {
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "GPGPU Functions")
	
protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
private:
};