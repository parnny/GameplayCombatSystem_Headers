// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/AnimNotify/SpellNotifyState.h"
#include "SpellNotifyState_Combo.generated.h"

UENUM(BlueprintType)
enum class ESpellNotifyStateComboType: uint8
{
	BlendOut,
	Immediately,
	Max,
};

UCLASS(BlueprintType)
class USpellNotifyStateInst_Combo : public USpellNotifyStateInst
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	ESpellNotifyStateComboType GetComboType() const;

	UFUNCTION(BlueprintPure)
	bool IsAIComboEnabled() const;
};
/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API USpellNotifyState_Combo : public USpellNotifyState
{
	GENERATED_BODY()
public:
	USpellNotifyState_Combo();

	virtual FString GetNotifyName_Implementation() const override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ESpellNotifyStateComboType ComboType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanAICombo = true;

	bool bDirty = false;
};
