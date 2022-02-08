// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatAbility : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void HandleCombatEffect(class UCombatEffect* CombatEffect);
};
