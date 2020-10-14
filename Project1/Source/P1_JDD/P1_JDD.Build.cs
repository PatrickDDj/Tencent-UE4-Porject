// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P1_JDD : ModuleRules
{
	public P1_JDD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
