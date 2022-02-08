// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayCombatEditor.h"

#include "AssetToolsModule.h"
#include "AssetTypeActions_CombatSpell.h"
#include "GameplayCombatEditorEdMode.h"
#include "SlateImageBrush.h"

#define LOCTEXT_NAMESPACE "FGameplayCombatEditorModule"

void FGameplayCombatEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FGameplayCombatEditorEdMode>(FGameplayCombatEditorEdMode::EM_GameplayCombatEditorEdModeId, LOCTEXT("GameplayCombatEditorEdModeName", "GameplayCombatEditorEdMode"), FSlateIcon(), true);

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		CombatSpellAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Combat")), LOCTEXT("Combat", "Combat"));
		CombatSpellAssetAction = MakeShareable(new FAssetTypeActions_CombatSpell(CombatSpellAssetCategory));
		AssetTools.RegisterAssetTypeActions(CombatSpellAssetAction.ToSharedRef());
	}
	//GEditor->OnBlueprintPreCompile().AddRaw(this, &FGameplayCombatEditorModule::OnBlueprintPreCompile);
}

void FGameplayCombatEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(CombatSpellAssetAction.ToSharedRef());
	}
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FGameplayCombatEditorEdMode::EM_GameplayCombatEditorEdModeId);
	
	//GEditor->OnBlueprintPreCompile().RemoveAll(this);
}

void FGameplayCombatEditorModule::OnBlueprintPreCompile(UBlueprint* BlueprintToCompile)
{
	BlueprintToCompile->GetName();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameplayCombatEditorModule, GameplayCombatEditor)