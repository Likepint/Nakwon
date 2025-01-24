// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DebuggingPlugin : ModuleRules
{
	public DebuggingPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				ModuleDirectory
			}
		);
				
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core"		
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "GameplayDebugger",

				"Nakwon"
			}
		);
	}
}
