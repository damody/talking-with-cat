// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AVGEditor : ModuleRules
{
	public AVGEditor(TargetInfo Target)
	{
		PrivateIncludePaths.AddRange(new string[] { 
			"AVGEditor/Public",
			"AVGEditor/Private"
		});

        PrivateDependencyModuleNames.AddRange(
            new string[] {
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"Paper2D", 
				"UnrealEd",
                "AVG"
			}
            );
		//PublicDependencyModuleNames			
	}
}
