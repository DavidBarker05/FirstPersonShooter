using UnrealBuildTool;

public class FirstPersonShooterEditor : ModuleRules
{
	public FirstPersonShooterEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"FirstPersonShooter"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"UnrealEd",
			"BlueprintGraph",
			"KismetCompiler"
		});
		
		PublicIncludePaths.AddRange(new string[]
        {
            "FirstPersonShooterEditor",
            "FirstPersonShooterEditor/Any"
        });
	}
}