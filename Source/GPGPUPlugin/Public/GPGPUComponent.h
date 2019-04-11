#pragma once

#include "CoreMinimal.h"

#include <vector>

#include "KernelArguments.h"

#include "GPGPUComponent.generated.h"

UCLASS(ClassGroup = "GPGPU", DisplayName = "GPGPU Component", HideCategories = (Tags), meta = (BlueprintSpawnableComponent))
class UGPGPUComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Kernel Functions", meta=(DeterminesOutputType = "kernelContainerClass"))
	static void ExecuteKernel(class UKernelContainer* kernelContainerAsset, UKernelArguments* kernelArguments, FIntVector gridOrGlobalDim, FIntVector blockOrWorkgroupDim);
	
protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
private:
};


