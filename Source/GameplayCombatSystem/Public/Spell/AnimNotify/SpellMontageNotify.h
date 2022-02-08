// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "SpellDefine.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "SpellMontageNotify.generated.h"

class USpellMontageNotify;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpellMontageNotify, USpellMontageNotify*, FGameplayTag);
/**
 * @brief 技能播放montage的通知类
 * 在montage中使用，在montage播放时触发
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API USpellMontageNotify : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
public:	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;

	virtual bool OnSpellNotified(USpell* Spell);
	/**
	 * @brief 事件标签
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag NotifyTag;
	
	FOnSpellMontageNotify OnSpellMontageNotify;
};
