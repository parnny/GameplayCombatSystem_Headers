// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/AnimNotify/SpellMontageNotify.h"
#include "SpellMontageNotify_SpellPriority.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API USpellMontageNotify_SpellPriority : public USpellMontageNotify
{
	GENERATED_BODY()
public:
	USpellMontageNotify_SpellPriority();
	
	virtual FString GetNotifyName_Implementation() const override;

	virtual bool OnSpellNotified(USpell* Spell) override;
	
	UPROPERTY(EditAnywhere)
	bool bResetToDefault = false;
	
	UPROPERTY(EditAnywhere,meta=(editcondition = "!bResetToDefault"))
	int32 SpellPriority = 0;
};
