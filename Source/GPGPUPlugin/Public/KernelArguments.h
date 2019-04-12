#pragma once

#include "CoreMinimal.h"

#pragma push_macro("CONSTEXPR")
#undef CONSTEXPR
#pragma push_macro("dynamic_cast")
#undef dynamic_cast
#pragma push_macro("check")
#undef check
#pragma push_macro("PI")
#undef PI

// include third-party headers with object names that conflict with UE4's macros
#include "boost/variant.hpp"

#pragma pop_macro("PI")
#pragma pop_macro("check")
#pragma pop_macro("dynamic_cast")
#pragma pop_macro("CONSTEXPR")

#include <vector>
#include <utility>

#include "KernelArguments.generated.h"

UCLASS(Blueprintable)
class UKernelArguments : public UObject {
	GENERATED_BODY()

public:
	static boost::variant<double, long long> SubParseProperty(UProperty* Property, void* ValuePtr);
	static void ParseProperty(FString variableName, UProperty* Property, void* ValuePtr, UKernelArguments* kernelArgs);
	static void IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr, UKernelArguments* kernelArgs);

    UFUNCTION(BlueprintCallable, Category = "Kernel Argument Functions", CustomThunk, meta=(CustomStructureParam = "kernelArgumentStructure"))
	static UKernelArguments* ParseKernelArgumentsFromStructure(UProperty* kernelArgumentStructure);
	DECLARE_FUNCTION(execParseKernelArgumentsFromStructure)
	{
		UKernelArguments* kernelArguments = NewObject<UKernelArguments>();
		Stack.Step(Stack.Object, NULL);
    	UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
 		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;
		P_NATIVE_BEGIN
		kernelArguments->InternalStructureProperty = StructProperty;
		kernelArguments->InternalStructPtr = StructPtr;
		IterateThroughStructProperty(StructProperty, StructPtr, kernelArguments);
		*(UKernelArguments**)Z_Param__Result = kernelArguments;
		P_NATIVE_END
	}

    UStructProperty* InternalStructureProperty;
	void* InternalStructPtr;
    std::vector<boost::variant<std::pair<FString, double>, std::pair<FString, long long>, std::pair<FString, std::vector<boost::variant<double, long long>>>>> Arguments;
protected:
private:
};