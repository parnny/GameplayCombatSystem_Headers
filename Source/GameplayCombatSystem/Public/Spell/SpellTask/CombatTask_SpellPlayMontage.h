// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameplayTask.h"
#include "SpellDefine.h"
#include "SpellNotifyState.h"

#include "CombatTask_SpellPlayMontage.generated.h"

class USpellMontageNotify;
/**
* @brief 异步任务的事件定义
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayMontageDelegate, FGameplayTag, EventTag, FSpellEventData, EventData);


class USpell;
/**
 * @brief 播放蒙太奇
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatTask_SpellPlayMontage : public UGameplayTask
{
	GENERATED_BODY()

public:
	/**
	 * @brief 技能播放蒙太奇任务入口
	 * @param Spell 技能实例
	 * @param MontageToPlay 蒙太奇资源
	 * @param PlayRate 播放速率
	 * @param StartSection 起始片段
	 * @param Priority
	 * @return 任务实例
	 */
	UFUNCTION(BlueprintCallable, meta = (HidePin = "Spell", DefaultToSelf = "Spell", BlueprintInternalUseOnly = "TRUE"))
	static UCombatTask_SpellPlayMontage* SpellPlayMontage(USpell* Spell, class UAnimMontage* MontageToPlay,
	                                                      float PlayRate = 1.f, FName StartSection = NAME_None,
	                                                      int32 Priority = 0);

	// >>>>>>>>>>> UGameplayTask
	virtual void Activate() override;

	/** The montage started blending out */
	UPROPERTY(BlueprintAssignable)
	FPlayMontageDelegate OnBlendOut;

	/** The montage completely finished playing */
	UPROPERTY(BlueprintAssignable)
	FPlayMontageDelegate OnCompleted;

	/** The montage was interrupted */
	UPROPERTY(BlueprintAssignable)
	FPlayMontageDelegate OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageDelegate OnNotify;

	void OnSpellCastCancelled();
	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted) const;
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void OnSpellMontageNotify(USpellMontageNotify* SpellNotify, FGameplayTag NotifyTag, USpell* CheckSpell) const;

	virtual void OnSpellNotifyStateBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                                     float TotalDuration, USpellNotifyStateInst* StateInst);
	virtual void OnSpellNotifyStateTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                                    float FrameDeltaTime, USpellNotifyStateInst* StateInst);
	virtual void OnSpellNotifyStateEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                                   USpellNotifyStateInst* StateInst);

	UPROPERTY()
	UAnimMontage* MontageToPlay;

protected:
	void PostMontageCompleted(UAnimMontage* Montage);
	void PostMontageInterrupted(UAnimMontage* Montage);

	virtual void OnDestroy(bool bInOwnerFinished) override;

	UAnimInstance* GetAnimInstance() const;

	UPROPERTY()
	USpell* Spell;

	int32 MontagePriority;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	float PlayRate;

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;

	int32 MontageInstanceID;
	FAnimMontageInstance* PlayMontageInstance;

	TMap<TWeakObjectPtr<USpellMontageNotify>, FDelegateHandle> SpellMontageNotifyHandlers;
	UPROPERTY()
	TMap<TWeakObjectPtr<USpellNotifyState>, USpellNotifyStateInst*> SpellNotifyStateInstances;

	/**
	 * @brief 技能取消的回调
	 */
	FDelegateHandle CancelledHandle;
};
