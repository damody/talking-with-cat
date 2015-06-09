// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AVG : ModuleRules
{
	public AVG(TargetInfo Target)
	{
		PrivateIncludePaths.AddRange(new string[] { 
			"AVG/Public",
			"AVG/Private"
		});

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"Paper2D", 
			}
			);
	}
}
