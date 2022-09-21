// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExodusSpace : ModuleRules
{
	public ExodusSpace(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;	
		// Core and my plugins
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "CroAction", "CroInventory", "CroMultiplayer" });
        // AI
        PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayTasks" });
        // UI
        PublicDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" });
        // Testing
        //PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
		// For steam
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
	}
}
