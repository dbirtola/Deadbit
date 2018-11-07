// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BotTestingEditorTarget : TargetRules
{
	public BotTestingEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "BotTesting" } );

        // Game editor
        ExtraModuleNames.AddRange(
            new string[]
            {
                //"TestWindowEditor"
            });
    }
}
