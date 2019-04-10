#include "GPGPUComponent.h"

class UKernelContainer* UGPGPUComponent::ConstructKernel(class UKernelContainer* kernelContainerAsset, UKernelArguments* kernelArguments) {
    return kernelContainerAsset;
}

UKernelArguments* ParseKernelArgumentsFromStructure(UProperty* kernelArgumentStructure) {
    UKernelArguments* args = NewObject<UKernelArguments>();
    return args;
}

void UGPGPUComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UGPGPUComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}
