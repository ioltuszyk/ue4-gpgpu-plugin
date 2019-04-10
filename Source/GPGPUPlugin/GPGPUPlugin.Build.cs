// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class GPGPUPlugin : ModuleRules
{
	private string ThirdPartyDirectory
	{
		get { return Path.Combine(ModuleDirectory, "..\\..\\ThirdParty"); }
	}

	public GPGPUPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		bEnableUndefinedIdentifierWarnings = false;
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
				"Core"
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
				"AssetTools",
				"ClassViewer",
				"UnrealEd"
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
		string BoostLibrariesPath = Path.Combine(OpenCLLibrariesPath, "Boost");
		if (Target.Platform == UnrealTargetPlatform.Win64) {
			string[] BoostLibs = Directory.GetFiles(BoostLibrariesPath, "*x64*.lib", SearchOption.AllDirectories);
			foreach (string boostLib in BoostLibs) {
				PublicAdditionalLibraries.Add(boostLib);
			}
		}
		else if (Target.Platform == UnrealTargetPlatform.Win32) {
			string[] BoostLibs = Directory.GetFiles(BoostLibrariesPath, "*x32*.lib", SearchOption.AllDirectories);
			foreach (string boostLib in BoostLibs) {
				PublicAdditionalLibraries.Add(boostLib);
			}
		}
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
