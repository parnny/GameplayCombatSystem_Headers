// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/AnimNotify/SpellNotifyState.h"
#include "SpellNotifyState_SpellPriority.generated.h"

UCLASS(BlueprintType)
class USpellNotifyStateInst_SpellPriority : public USpellNotifyStateInst
{
	GENERATED_BODY()
public:
	virtual void NotifySpellBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifySpellEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	int32 PreSpellPriority = 0;
};

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API USpellNotifyState_SpellPriority : public USpellNotifyState
{
	GENERATED_UCLASS_BODY()
	
	FString GetNotifyName_Implementation() const override;
	
	UPROPERTY(EditAnywhere)
	int32 SpellPriority = 0;
};
