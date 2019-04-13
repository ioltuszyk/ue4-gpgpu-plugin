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
#include "cuda.h"
#include "nvrtc.h"
#include "builtin_types.h"

#pragma pop_macro("PI")
#pragma pop_macro("check")
#pragma pop_macro("dynamic_cast")
#pragma pop_macro("CONSTEXPR")

#include <vector>
#include <algorithm>

#include "KernelContainer.h"
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


