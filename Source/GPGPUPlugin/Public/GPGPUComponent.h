#pragma once

#include "CoreMinimal.h"

#include <vector>

#include "KernelArguments.h"

#include "GPGPUComponent.generated.h"

UCLASS(ClassGroup = "GPGPU", DisplayName = "GPGPU Component", HideCategories = (Tags), meta = (BlueprintSpawnableComponent))
class UGPGPUComponent : public UActorComponent {
	GENERATED_BODY()

public:
	static boost::variant<double, long long> SubParseProperty(UProperty* Property, void* ValuePtr);
	static void ParseProperty(UProperty* Property, void* ValuePtr, UGPGPUComponent* componentInst);
	static void IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr, UGPGPUComponent* componentInst);

	UFUNCTION(BlueprintCallable, Category = "GPGPU Functions", meta=(DeterminesOutputType = "kernelContainerClass"))
	static class UKernelContainer* ConstructKernel(class UKernelContainer* kernelContainerAsset, UKernelArguments* kernelArguments);
	
	UFUNCTION(BlueprintCallable, Category = "GPGPU Functions", CustomThunk, meta=(CustomStructureParam = "kernelArgumentStructure"))
	static void ParseKernelArgumentsFromStructure(UProperty* kernelArgumentStructure, UGPGPUComponent* componentInst);
	DECLARE_FUNCTION(execParseKernelArgumentsFromStructure)
	{
		Stack.Step(Stack.Object, NULL);
    	UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
 		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_GET_OBJECT(UGPGPUComponent, componentInst);
		P_FINISH;

		IterateThroughStructProperty(StructProperty, StructPtr, componentInst);
	}

	UPROPERTY(BlueprintReadOnly)
	UKernelArguments* kernelArguments;
protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
private:
};


