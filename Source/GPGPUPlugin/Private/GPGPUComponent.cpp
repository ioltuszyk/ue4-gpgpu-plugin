#include "GPGPUComponent.h"

class ArgumentVisitor : public boost::static_visitor<>
{
public:
	ArgumentVisitor( UKernelArguments* kArgs ) : KArgs( kArgs ) {}

	void operator()(std::pair<FString, double> v) {
		UScriptStruct* Struct = KArgs->InternalStructureProperty->Struct;
		for (TFieldIterator<UProperty> It(Struct); It; ++It)
		{
			UProperty* Property = *It;
			FString VariableName = Property->GetName();
			if (VariableName==v.first) {
				UNumericProperty *NumericProperty = (Cast<UNumericProperty>(Property));
				NumericProperty->SetFloatingPointPropertyValue(Property->ContainerPtrToValuePtr<void>(KArgs->InternalStructPtr, 0), v.second);
			}
		}
	}
	void operator()(std::pair<FString, long long> v) {
		UScriptStruct* Struct = KArgs->InternalStructureProperty->Struct;
		for (TFieldIterator<UProperty> It(Struct); It; ++It)
		{
			UProperty* Property = *It;
			FString VariableName = Property->GetName();
			if (VariableName==v.first) {
				UNumericProperty *NumericProperty = (Cast<UNumericProperty>(Property));
				NumericProperty->SetIntPropertyValue(Property->ContainerPtrToValuePtr<void>(KArgs->InternalStructPtr, 0), v.second);
			}
		}
	}
	void operator()(std::pair<FString, std::vector<boost::variant<double, long long>>> v) {
		UScriptStruct* Struct = KArgs->InternalStructureProperty->Struct;
		for (TFieldIterator<UProperty> It(Struct); It; ++It)
		{
			UProperty* Property = *It;
			FString VariableName = Property->GetName();
			if (VariableName==v.first) {
				FScriptArrayHelper Helper(Cast<UArrayProperty>(Property), Property->ContainerPtrToValuePtr<void>(KArgs->InternalStructPtr, 0));
				UProperty* intermediateProp = (Cast<UArrayProperty>(Property))->Inner;
				for (int32 i = 0, n = Helper.Num(); i<n; ++i)
				{
					if (UNumericProperty *NumericProperty = Cast<UNumericProperty>(intermediateProp))
					{
						if (NumericProperty->IsFloatingPoint())
						{
							NumericProperty->SetFloatingPointPropertyValue(Helper.GetRawPtr(i), boost::get<double>(v.second[i]));
						}
						else if (NumericProperty->IsInteger())
						{
							NumericProperty->SetIntPropertyValue(Helper.GetRawPtr(i), boost::get<long long>(v.second[i]));
						}
					}
				}
			}
		}
	}

private:
    UKernelArguments* KArgs;
};

void UGPGPUComponent::ExecuteKernel(class UKernelContainer* kernelContainerAsset, UKernelArguments* kernelArguments, FIntVector gridOrGlobalDim, FIntVector blockOrWorkgroupDim) {
	ArgumentVisitor argumentVisitor(kernelArguments);
	std::for_each(kernelArguments->Arguments.begin(), kernelArguments->Arguments.end(),
	boost::apply_visitor(argumentVisitor));
}

void UGPGPUComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UGPGPUComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}
