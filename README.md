# Unreal Engine 4 Content Module for OpenCL and CUDA

[![GitHub release](https://img.shields.io/github/release/ioltuszyk/ue4-gpgpu-plugin.svg)](https://github.com/ioltuszyk/ue4-gpgpu-plugin/releases)
[![Github All Releases](https://img.shields.io/github/downloads/ioltuszyk/ue4-gpgpu-plugin/total.svg)](https://github.com/ioltuszyk/ue4-gpgpu-plugin/releases)

Facilitates UE4 developers with a baseline system for integrating OpenCL and/or CUDA kernels into their projects' workflows. 

Installation
----------------------

1. Ensure your CUDA/OpenCL device's drivers are up-to-date.
  * [Intel](https://software.intel.com/en-us/articles/opencl-drivers)
  * [NVIDIA](https://www.nvidia.com/Download/index.aspx?lang=en-us)
  * [AMD](https://www.amd.com/en/support)
2. Copy or move the 'Plugins' folder into your project's root directory.

Limitations
----------------------

1. Run-time compilation of CUDA modules is performed using [NVRTC](https://docs.nvidia.com/cuda/nvrtc/index.html), which requires a 64-bit system configuration on the Windows platform.
2. Does not allow for specification of device to execute kernel on (select the first one available for a given GPGPU framework)
3. Requires that header-only libraries be written inline in the module code contained in the kernel asset.

Usage
----------------------

