// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SpellNotifyState.generated.h"

class USpellNotifyStateInst;
class USpell;
class USpellNotifyState;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSpellNotifyStateBegin, USkeletalMeshComponent*, UAnimSequenceBase*, float);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSpellNotifyStateTick, USkeletalMeshComponent*, UAnimSequenceBase*, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpellNotifyStateEnd, USkeletalMeshComponent*, UAnimSequenceBase*);


UENUM(BlueprintType,Blueprintable)
enum class ESpellNotifyStateEntryType: uint8
{
	NotifyBegin,
	NotifyTick,
	NotifyEnd,
	Interrupted,
};

UCLASS(BlueprintType)
class USpellNotifyStateInst : public UObject
{
	GENERATED_BODY()
public:
	virtual void BeginDestroy() override;
	
	USpell* GetSpell() const
	{
		return Spell.Get();
	}

	void Init(USpell* InSpell, USpellNotifyState* InSpellNotifyState);

	bool IsInstValid() const;
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<USpell> Spell;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<USpellNotifyState> SpellNotifyState;

	FDelegateHandle HandleBegin;
	FDelegateHandle HandleTick;
	FDelegateHandle HandleEnd;

	UPROPERTY(BlueprintReadWrite)
	bool bTickable = true;

	UPROPERTY()
	UObject* DebugOuter = nullptr;
	
	/**
	 * @brief 状态持续时间
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float StateDuration;
	
	virtual void NotifySpellBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);
	virtual void NotifySpellTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime);
	virtual void NotifySpellEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);

private:
	void FindFunctionHandler();
private:
	TWeakObjectPtr<UFunction> HandlerFunction;
	struct
	{
		UObject* Object = nullptr;
		ESpellNotifyStateEntryType Type;
	} FuncParams;
};

/**
 * @brief 技能播放montage时，拓展的动作状态
 * 在Montage中使用，用于标记动作状态
 */
UCLASS(BlueprintType,Blueprintable)
class GAMEPLAYCOMBATSYSTEM_API USpellNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	friend class USpellNotifyStateInst;
public:
	/**
	 * @brief 初始化
	 * @param InSpell 技能实例
	 */
	 void Init(const USpell* InSpell);
	/**
	 * @brief 改状态的标签
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag NotifyTag;
	
	UPROPERTY(VisibleAnywhere)
	FName HandlerFunctionName;

	// >>>>>>>>>>> UAnimNotifyState
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override final;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override final;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override final;

	virtual USpellNotifyStateInst* CreateSpellNotifyStateInst(UObject*Outer, USpell* Spell);

	UFUNCTION(BlueprintCallable)
	void SetTickable(bool Tickable);
	
	FOnSpellNotifyStateBegin SpellNotifyStateBegin;
	FOnSpellNotifyStateTick SpellNotifyStateTick;
	FOnSpellNotifyStateEnd SpellNotifyStateEnd;
	
#if WITH_EDITOR
	virtual bool CanBePlaced(UAnimSequenceBase* Animation) const override;
#endif
	
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bTickable = true;
	
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<USpellNotifyStateInst> InstanceClass;
};
