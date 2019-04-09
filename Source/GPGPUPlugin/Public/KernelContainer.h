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

UCLASS(Blueprintable)
class UKernelContainer : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kernel Parameters")
	TEnumAsByte<EKernelContainer::KernelType> KernelType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kernel Parameters")
    FText KernelCode;
protected:
private:
};