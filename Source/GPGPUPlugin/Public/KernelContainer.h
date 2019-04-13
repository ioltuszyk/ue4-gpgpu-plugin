#pragma once

#include "CoreMinimal.h"

#include "KernelContainer.generated.h"

UENUM()
namespace EKernelContainer {
	enum KernelType {
		kCUDA		UMETA(DisplayName = "CUDA"),
		kOpenCL		UMETA(DisplayName = "Open CL")
	};
}

UCLASS(BlueprintType)
class UKernelContainer : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kernel Parameters")
	TEnumAsByte<EKernelContainer::KernelType> KernelType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kernel Parameters", meta = (MultiLine = "true"))
    FText KernelCode;
protected:
private:
};