#pragma once

#include "CoreMinimal.h"

#include "KernelArguments.h"

#include "GPGPUComponent.generated.h"

UCLASS(ClassGroup = "GPGPU", DisplayName = "GPGPU Component", HideCategories = (Tags), meta = (BlueprintSpawnableComponent))
class UGPGPUComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GPGPU Functions", meta=(DeterminesOutputType = "kernelContainerClass"))
	static class UKernelContainer* ConstructKernel(class UKernelContainer* kernelContainerAsset, UKernelArguments* kernelArguments);
	
	UFUNCTION(BlueprintCallable, Category = "GPGPU Functions", CustomThunk, meta=(CustomStructureParam = "kernelArgumentStructure"))
	static UKernelArguments* ParseKernelArgumentsFromStructure(UProperty* kernelArgumentStructure);
	DECLARE_FUNCTION(execParseKernelArgumentsFromStructure)
	{
		Stack.Step(Stack.Object, NULL);
    	UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
 		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;
		//IterateThroughStructProperty(StructProperty, StructPtr);
	}
protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
private:
};