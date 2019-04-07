// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class ue4_gpgpu_plugin : ModuleRules
{
	private string ThirdPartyDirectory
	{
		get { return Path.Combine(ModuleDirectory, "..\\..\\ThirdParty"); }
	}

	public ue4_gpgpu_plugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ThirdPartyDirectory, "Include")
				// ... add public include paths required here ...
			}
			);
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
		string OpenCLLibrariesPath = Path.Combine(ThirdPartyDirectory, "Lib");
		string NvidiaLibrariesPath = Path.Combine(OpenCLLibrariesPath, "NVIDIA", PlatformString);
		string IntelLibrariesPath = Path.Combine(OpenCLLibrariesPath, "Intel", PlatformString);
		string AmdLibrariesPath = Path.Combine(OpenCLLibrariesPath, "AMD", PlatformString);
		if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
		{
			PublicAdditionalLibraries.Add(Path.Combine(NvidiaLibrariesPath, "OpenCL.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(IntelLibrariesPath, "OpenCL.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(AmdLibrariesPath, "OpenCL.lib"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalFrameworks.Add(new UEBuildFramework("OpenCL"));
		}
	}
}
