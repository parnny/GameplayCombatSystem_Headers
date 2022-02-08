// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatEventInterface.generated.h"

class ACombatant;
class UCombatEvent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI,meta = (CannotImplementInterfaceInBlueprint))
class UCombatEventInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API ICombatEventInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual void HandleCombatEvent(const UCombatEvent* CombatEvent) = 0;

	UFUNCTION(BlueprintCallable)
	virtual void CallSubHandleFunction(const UCombatEvent* CombatEvent);
	
	virtual int32 GetHandlePriority() { return 0; };
};