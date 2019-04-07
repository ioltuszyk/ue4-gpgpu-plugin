// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ue4_gpgpu_plugin.h"

#define LOCTEXT_NAMESPACE "Fue4_gpgpu_pluginModule"

void Fue4_gpgpu_pluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void Fue4_gpgpu_pluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fue4_gpgpu_pluginModule, ue4_gpgpu_plugin)