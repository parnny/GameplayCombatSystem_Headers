// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "IAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FGameplayCombatEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	void OnBlueprintPreCompile(UBlueprint* BlueprintToCompile);
	
private:
	EAssetTypeCategories::Type CombatSpellAssetCategory;
	TSharedPtr<IAssetTypeActions> CombatSpellAssetAction;
};
