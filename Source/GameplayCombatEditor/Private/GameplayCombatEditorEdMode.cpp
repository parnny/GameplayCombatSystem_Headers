// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayCombatEditorEdMode.h"
#include "GameplayCombatEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FGameplayCombatEditorEdMode::EM_GameplayCombatEditorEdModeId = TEXT("EM_GameplayCombatEditorEdMode");

FGameplayCombatEditorEdMode::FGameplayCombatEditorEdMode()
{

}

FGameplayCombatEditorEdMode::~FGameplayCombatEditorEdMode()
{

}

void FGameplayCombatEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FGameplayCombatEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FGameplayCombatEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FGameplayCombatEditorEdMode::UsesToolkits() const
{
	return true;
}




