// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatEffectPlayer.generated.h"

class ACombatant;
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCombatEffectPlayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API ICombatEffectPlayer
{
	GENERATED_IINTERFACE_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION(BlueprintImplementableEvent)
	void PlayEffect(ACombatant* DesCombatant, UObject* ApplySpec);
};
