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

UCLASS()
class UKernelArguments : public UObject {
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "Kernel Functions")
    void LogArguments();

    std::vector<boost::variant<double, long long, std::vector<boost::variant<double, long long>>>> Arguments;
private:
};