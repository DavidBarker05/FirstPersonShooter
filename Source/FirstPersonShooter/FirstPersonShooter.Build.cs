// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstPersonShooter : ModuleRules
{
	public FirstPersonShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"UMG",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"FirstPersonShooter",
			"FirstPersonShooter/Any",
			"FirstPersonShooter/Character",
			"FirstPersonShooter/Character/StateMachine",
			"FirstPersonShooter/Character/Components",
			"FirstPersonShooter/Events",
			"FirstPersonShooter/Factories",
			"FirstPersonShooter/HealthPickup",
			"FirstPersonShooter/Interfaces",
			"FirstPersonShooter/Weapons",
			"FirstPersonShooter/Weapons/Components",
			"FirstPersonShooter/Weapons/Pistol",
			"FirstPersonShooter/Weapons/Rifle",
			"FirstPersonShooter/Weapons/Rifle/RiflePickup"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}