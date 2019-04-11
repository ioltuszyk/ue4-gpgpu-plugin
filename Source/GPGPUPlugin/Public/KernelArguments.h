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

#include "KernelArguments.generated.h"

UCLASS(Blueprintable)
class UKernelArguments : public UObject {
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Kernel Arguments From Class", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
    static UKernelArguments* CreateKernelArguments(UObject* WorldContextObject);

	static boost::variant<double, long long> SubParseProperty(UProperty* Property, void* ValuePtr);
	static void ParseProperty(UProperty* Property, void* ValuePtr, UKernelArguments* kernelArgs);
	static void IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr, UKernelArguments* kernelArgs);

    UFUNCTION(BlueprintCallable, Category = "Kernel Argument Functions", CustomThunk, meta=(CustomStructureParam = "kernelArgumentStructure"))
	static void ParseKernelArgumentsFromStructure(UProperty* kernelArgumentStructure, UKernelArguments* kernelArgs);
	DECLARE_FUNCTION(execParseKernelArgumentsFromStructure)
	{
		Stack.Step(Stack.Object, NULL);
    	UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
 		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_GET_OBJECT(UKernelArguments, kernelArgs);
		P_FINISH;

		IterateThroughStructProperty(StructProperty, StructPtr, kernelArgs);
	}
    
    std::vector<boost::variant<double, long long, std::vector<boost::variant<double, long long>>>> Arguments;
private:
};