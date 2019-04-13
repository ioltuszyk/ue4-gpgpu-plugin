#include "GPGPUComponent.h"

#ifdef  __cuda_cuda_h__

#ifndef checkCudaErrors
#define checkCudaErrors(err)  __checkCudaErrors (err, __FILE__, __LINE__)

// These are the inline versions for all of the SDK helper functions
inline void __checkCudaErrors(CUresult err, const char* file, const int line)
{
	if (CUDA_SUCCESS != err)
	{
		UE_LOG(LogTemp, Warning, TEXT("CUDA: Check Error"));
	}
}
#endif
#ifdef getLastCudaDrvErrorMsg
#undef getLastCudaDrvErrorMsg
#endif

#define getLastCudaDrvErrorMsg(msg)           __getLastCudaDrvErrorMsg  (msg, __FILE__, __LINE__)

inline void __getLastCudaDrvErrorMsg(const char* msg, const char* file, const int line)
{
	CUresult err = cuCtxSynchronize();

	if (CUDA_SUCCESS != err)
	{
		UE_LOG(LogTemp, Warning, TEXT("CUDA: Task Failed"));
		exit(EXIT_FAILURE);
	}
}

// This function wraps the CUDA Driver API into a template function
template <class T>
inline void getCudaAttribute(T* attribute, CUdevice_attribute device_attribute, int device)
{
	CUresult error_result = cuDeviceGetAttribute(attribute, device_attribute, device);

	if (error_result != CUDA_SUCCESS)
	{
		UE_LOG(LogTemp, Warning, TEXT("CUDA: Failed to Retrieve Attribute"));
		exit(EXIT_SUCCESS);
	}
}
#endif

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

void setVar(CUdeviceptr* d_a) {
	cuMemAlloc(d_a, sizeof(int) * 3);
}

void UGPGPUComponent::ExecuteKernel(class UKernelContainer* kernelContainerAsset, UKernelArguments* kernelArguments, FIntVector gridOrGlobalDim, FIntVector blockOrWorkgroupDim) {

	// temp
	char* kernel_name = (char*) "kernel";
	//

	// Code containing (potentially) multiple kernels
	FString Fcuda_code= (kernelContainerAsset->KernelCode).ToString();
	std::string str_cuda_code = std::string(TCHAR_TO_UTF8(*Fcuda_code));
	const char* cuda_code = str_cuda_code.c_str();
	
	int device;
	int deviceIndex = 0;
	CUcontext  context;
	CUmodule   module;
	CUfunction kernel;
	size_t     totalGlobalMem;
	int deviceCount = 0;
	CUresult err = cuInit(0);
	if (CUDA_SUCCESS == err)
	{
		checkCudaErrors(cuDeviceGetCount(&deviceCount));
		if (deviceCount != 0)
		{
			checkCudaErrors(cuDeviceGet(&device, deviceIndex));
			char name[100];
			cuDeviceGetName(name, 100, device);
			int computeMode;
			getCudaAttribute<int>(&computeMode, CU_DEVICE_ATTRIBUTE_COMPUTE_MODE, deviceIndex);
			if (computeMode == CU_COMPUTEMODE_PROHIBITED) {
				UE_LOG(LogTemp, Warning, TEXT("CUDA: Thread Execution Prohibited on Device Named: %s"), *FString(ANSI_TO_TCHAR(name)));
				return;
			}
			checkCudaErrors(cuDeviceTotalMem(&totalGlobalMem, device));
			UE_LOG(LogTemp, Display, TEXT("CUDA: Executing kernel on device named: %s"), *FString(ANSI_TO_TCHAR(name)));
			UE_LOG(LogTemp, Display, TEXT("CUDA: Global memory: %llu bytes"), totalGlobalMem);
			err = cuCtxCreate(&context, 0, device);
			if (err != CUDA_SUCCESS) {
				UE_LOG(LogTemp, Warning, TEXT("CUDA: Failed to Initialize Context"));
				cuCtxDetach(context);
				return;
			}
			nvrtcProgram prog;
			nvrtcResult createResult = nvrtcCreateProgram(&prog,			// prog
				cuda_code,							// buffer
				NULL,							// name
				0,								// numHeaders
				NULL,							// headers
				NULL);							// includeNames
			const char* opts[] = { "--gpu-architecture=compute_30",
				"--fmad=false" };
			nvrtcResult compileResult = nvrtcCompileProgram(prog,							// prog
				2,								// numOptions
				opts);							// options
			size_t ptxSize;
			nvrtcGetPTXSize(prog, &ptxSize);
			char* ptx = new char[ptxSize];
			nvrtcGetPTX(prog, ptx);
			nvrtcDestroyProgram(&prog);
			err = cuModuleLoadDataEx(&module, ptx, 0, 0, 0);
			if (err != CUDA_SUCCESS) {
				UE_LOG(LogTemp, Warning, TEXT("CUDA: Error Loading Module"));
				cuCtxDetach(context);
				return;
			}
			// seperate out into seperate function
			err = cuModuleGetFunction(&kernel, module, kernel_name);
			if (err != CUDA_SUCCESS) {
				UE_LOG(LogTemp, Warning, TEXT("CUDA: Error Retrieving Module Function: %s"));
				cuCtxDetach(context);
				return;
			}
			// allocate memory from kernelArguments->Arguments and call cuLaunchKernel
			ArgumentVisitor argumentVisitor(kernelArguments);
			std::for_each(kernelArguments->Arguments.begin(), kernelArguments->Arguments.end(),
				boost::apply_visitor(argumentVisitor));
			cuCtxDetach(context);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("CUDA: No Supported Devices Detected"));
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
