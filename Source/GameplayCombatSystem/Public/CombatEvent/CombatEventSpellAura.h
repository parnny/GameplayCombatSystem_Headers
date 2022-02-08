// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Aura.h"
#include "CombatEvent/CombatEventSpell.h"
#include "CombatEventSpellAura.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventAura : public UCombatEvent
{
	GENERATED_BODY()
	
public:
	UCombatEventAura()
        : Super()
	{
		EventCategory = "AURA";
	}

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UAura> Aura;
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventAuraApplied : public UCombatEventAura
{
	GENERATED_BODY()
public:
	UCombatEventAuraApplied()
        : Super()
	{
		EventName = "APPLIED";
	}
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventAuraRefreshed : public UCombatEventAura
{
	GENERATED_BODY()
	public:
	UCombatEventAuraRefreshed()
        : Super()
	{
		EventName = "REFRESH";
	}
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventAuraRemoved : public UCombatEventAura
{
	GENERATED_BODY()
	public:
	UCombatEventAuraRemoved()
        : Super()
	{
		EventName = "REMOVED";
	}
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventAuraAppliedDose : public UCombatEventAura
{
	GENERATED_BODY()
	public:
	UCombatEventAuraAppliedDose()
        : Super()
	{
		EventName = "APPLIED_DOSE";
	}
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventAuraRemovedDose : public UCombatEventAura
{
	GENERATED_BODY()
	public:
	UCombatEventAuraRemovedDose()
        : Super()
	{
		EventName = "REMOVED_DOSE";
	}
};