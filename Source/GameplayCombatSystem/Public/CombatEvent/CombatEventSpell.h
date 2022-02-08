// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Spell.h"
#include "CombatEvent/CombatEvent.h"
#include "CombatEventSpell.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventSpell : public UCombatEvent
{
	GENERATED_BODY()
public:
	UCombatEventSpell()
		: Super()
	{
		EventCategory = "SPELL";
	}

	virtual FString GetEventDesc() const override
	{
		if (Spell.IsValid())
		{
			return Spell->GetName();
		}
		return Super::GetEventDesc();
	}
	
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<USpell> Spell;
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventSpellCastStart : public UCombatEventSpell
{
	GENERATED_BODY()
public:
	UCombatEventSpellCastStart()
        : Super()
	{
		EventName = "CAST_START";
	}
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventSpellCastSuccess : public UCombatEventSpell
{
	GENERATED_BODY()
public:
	UCombatEventSpellCastSuccess()
	    : Super()
	{
		EventName = "CAST_SUCCESS";
	}
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventSpellCastFinish : public UCombatEventSpell
{
	GENERATED_BODY()
public:
	UCombatEventSpellCastFinish()
        : Super()
	{
		EventName = "CAST_FINISH";
	}
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag FailedCode;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsSuccessful;
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventSpellCharge : public UCombatEventSpell
{
	GENERATED_BODY()
	public:
	UCombatEventSpellCharge()
        : Super()
	{
		EventName = "CHARGE_COOLDOWN";
	}
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventSpellMontage : public UCombatEventSpell
{
	GENERATED_BODY()
public:
	UCombatEventSpellMontage()
		: Super()
	{
		EventName = "MONTAGE";
	}
	/**
	* @brief 事件标签
	*/
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FGameplayTag MontageTag;
};

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventSpellPriority : public UCombatEventSpell
{
	GENERATED_BODY()
public:
	UCombatEventSpellPriority()
		: Super()
	{
		EventName = "PRIORITY";
	}
	/**
	* @brief 事件标签
	*/
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	int32 PrePriority;
};