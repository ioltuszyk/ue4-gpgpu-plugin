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

typedef boost::variant<int> kernelArg;

UCLASS()
class UKernelArguments : public UObject {
	GENERATED_BODY()

public:
private:
    std::vector<kernelArg> m_Arguments;
};