// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatEvent/CombatEventSpell.h"
#include "CombatEventEffect.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventEffect : public UCombatEvent
{
	GENERATED_BODY()
public:
	UCombatEventEffect()
        : Super()
	{
		EventCategory = "EFFECT";
	}

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UCombatEffect> CombatEffect;
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventEffectApplied : public UCombatEventEffect
{
	GENERATED_BODY()
public:
	UCombatEventEffectApplied()
        : Super()
	{
		EventName = "APPLIED";
	}
	
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> ApplyTarget;

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UObject> ApplySpec;
};