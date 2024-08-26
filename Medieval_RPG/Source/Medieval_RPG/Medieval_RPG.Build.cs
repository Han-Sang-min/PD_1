// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Medieval_RPG : ModuleRules
{
	public Medieval_RPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"EnhancedInput",
		});

		PublicIncludePaths.AddRange(new string[] {
			"Medieval_RPG/Core/Public",
			/* Character */
			"Medieval_RPG/Character/Player/Public",
			"Medieval_RPG/Character/Component/Public",
			/* Level */
			"Medieval_RPG/Level/Main/GameMode/Public",
			"Medieval_RPG/Level/Test/GameMode/Public",
		});
	}
}
