#include "GPGPUComponent.h"

class UKernelContainer* UGPGPUComponent::ConstructKernel(class UKernelContainer* kernelContainerAsset, UKernelArguments* kernelArgs) {
    return kernelContainerAsset;
}

void UGPGPUComponent::ParseKernelArgumentsFromStructure(UProperty* kernelArgumentStructure, UGPGPUComponent* componentInst) {
    check(0);
}

boost::variant<double, long long> UGPGPUComponent::SubParseProperty(UProperty* Property, void* ValuePtr) {
    if (UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property))
    {
        if (NumericProperty->IsFloatingPoint())
        {
            return NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
        }
        else if (NumericProperty->IsInteger())
        {
            return NumericProperty->GetSignedIntPropertyValue(ValuePtr);
        }
    }
    return (double)0.0f;
}

void UGPGPUComponent::ParseProperty(UProperty* Property, void* ValuePtr, UGPGPUComponent* componentInst)
{        
    if (UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property))
    {
        if (NumericProperty->IsFloatingPoint())
        {
            componentInst->kernelArguments->Arguments.push_back(NumericProperty->GetFloatingPointPropertyValue(ValuePtr));
        }
        else if (NumericProperty->IsInteger())
        {
            componentInst->kernelArguments->Arguments.push_back(NumericProperty->GetSignedIntPropertyValue(ValuePtr));
        }
    }
    if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
    {      
        std::vector<boost::variant<double, long long>> subArguments;
        FScriptArrayHelper Helper(ArrayProperty, ValuePtr);
        
        for (int32 i = 0, n = Helper.Num(); i<n; ++i)
        {    
            subArguments.push_back(SubParseProperty(ArrayProperty->Inner, Helper.GetRawPtr(i)));
        }
        componentInst->kernelArguments->Arguments.push_back(subArguments);
    }
}

void UGPGPUComponent::IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr, UGPGPUComponent* componentInst) {
    componentInst->kernelArguments = NewObject<UKernelArguments>();
    UScriptStruct* Struct = StructProperty->Struct;
    for (TFieldIterator<UProperty> It(Struct); It; ++It)
    {
        UProperty* Property = *It;
        FString VariableName = Property->GetName();
        for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++)
        {
            void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, ArrayIndex);
            ParseProperty(Property, ValuePtr, componentInst);
        }
    }
}

void UGPGPUComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UGPGPUComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}
