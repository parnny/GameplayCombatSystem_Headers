// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "CombatEffect.h"
#include "CombatEventInterface.h"
#include "CombatTagInterface.h"
#include "CombatTask_Interval.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "GameplayTaskOwnerInterface.h"
#include "SpellDefine.h"
#include "CombatWorldObject.h"

#include "Spell.generated.h"

class USpellNotifyStateInst;
class UCombatTask_SpellPlayMontage;
class USpellNotifyState;
class USpellMontageNotify;
class UCombatEffect;

DECLARE_MULTICAST_DELEGATE(FOnSpellCastCancelled);
/**
 * @brief 技能的状态
 */
UENUM(BlueprintType,Blueprintable)
enum class ESpellState : uint8
{
	Ready UMETA(DisplayName = "就绪"),
	Casting UMETA(DisplayName = "施法中"),
};

/**
 * @brief 战斗技能
 * 可以响应战斗事件 HandleCombatEvent
 * 包含各种战斗效果 CombatEffect
 *
 * 蓝图实现：
 *	BP_OnSpellCreated 技能创建
 *	BP_OnSpellCastStart 技能释放开始
 *	
 */
UCLASS(Blueprintable,BlueprintType,meta=( BlueprintInternalUseOnly="true" ))
class GAMEPLAYCOMBATSYSTEM_API USpell
	: public UCombatWorldObject
	, public ICombatEventInterface
	, public IGameplayTaskOwnerInterface
	, public ICombatEffectInstigator
	, public ICombatTagInterface
{
	GENERATED_UCLASS_BODY()

	// ----------------------- 技能基础接口 ----------------------------
public:
	/**
	 * @brief 初始化技能，创建技能的效果实例，设置初始状态
	 *	蓝图：BP_OnSpellCreated
	 */
	void InitSpell();
	/**
	 * @brief 技能销毁，释放效果实例
	 */
	void DestroySpell();
	/**
	 * @brief 技能更新
	 * @param DeltaTime 时间
	 * @param TickType Tick类型
	 */
	void TickSpell(float DeltaTime, ELevelTick TickType);
	
protected:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnSpellCreated"))
    void BP_OnSpellCreated();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnSpellDestroy"))
	void BP_OnSpellDestroy();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSpellTick"))
	void BP_OnSpellTick(float DeltaTime);

	// ----------------------- 技能属性接口 ----------------------------
public:
	/**
	 * @brief 设置技能所属
	 * @param NewOwner 技能所属
	 */
	UFUNCTION(BlueprintCallable)
	void SetSpellOwner(ACombatant* NewOwner);
	/**
	* @brief获取技能所属
	* @return 技能所属
	*/
	UFUNCTION(BlueprintPure)
    ACombatant* GetSpellOwner() const;
	/**
	 * @brief 设置技能名称
	 * @param NewName 技能名称
	 */
	UFUNCTION(BlueprintCallable)
    void SetSpellName(FName NewName);
	/**
	 * @brief 获取技能所属者的Avatar
	 * @return 技能所属者的Avatar
	 */
	UFUNCTION(BlueprintPure)
	ACombatAvatar* GetSpellAvatar() const;
	/**
	* @brief 获取当前技能状态
	* @return 当前技能状态
	*/
	UFUNCTION(BlueprintPure)
    ESpellState GetSpellState() const;
	// ----------------------- 技能表现 ----------------------------
	/**
	 * @brief 施法者朝向技能目标
	 */
	UFUNCTION(BlueprintCallable)
    void LookAtSpellTarget() const;
	
	// ----------------------- 技能使用接口 ----------------------------
	/**
	 * @brief 判断技能当前是否能够释放，目前只检测了消耗
	 * @param ConsumeScale 消耗系数，相乘关系
	 * @param Insufficient
	 * @return 是否可以释放
	 */
	UFUNCTION(BlueprintPure)
    bool CheckSpellCost(float ConsumeScale,FSpellInsufficientCost& Insufficient);
	/**
	 * @brief 执行技能消耗
	 * @param ConsumeScale 消耗系数，相乘关系, 充能消耗不受此字段影响
	 * @return 是否成功消耗
	 */
	UFUNCTION(BlueprintCallable)
	bool ApplySpellCost(float ConsumeScale=1.f);
	/**
	* @brief 执行技能冷却
	*/
	UFUNCTION(BlueprintCallable)
	void ApplySpellCooldown();
	
	/**
	 * @brief 释放技能
	 * @param CastParam 技能参数
	 */
	UFUNCTION(BlueprintCallable)
    bool CastSpell(const FSpellCastParameter CastParam, FGameplayTagContainer& Errors);

	UFUNCTION(BlueprintCallable)
	void CancelSpell(const FGameplayTag Code);
	/**
	 * @brief 获取技能充能
	 * @param ChargeValue 充能次数
	 */
	UFUNCTION(BlueprintCallable)
	void ChargeSpell(const int32 ChargeValue);
	/**
	 * @brief 获取技能充能
	 * @return 技能充能信息
	 */
	UFUNCTION(BlueprintPure)
    FSpellCharge GetSpellCharge() const;

	UFUNCTION(BlueprintPure)
	FFloatRange GetSpellRange() const;
	
	UFUNCTION(BlueprintPure)
    bool IsInSpellRange(ACombatant* OtherCombatant=nullptr,bool bExcludeCapsule=true) const;

	UFUNCTION(BlueprintPure)
	bool IsCasting() const;

	UFUNCTION(BlueprintPure)
	bool IsCastSuccessful() const;

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	bool IsCastable(const FSpellCastParameter CastData, FGameplayTagContainer& Errors);
	
	UFUNCTION(BlueprintCallable)
	void ResetSpellPriority();

	UFUNCTION(BlueprintCallable)
	void SetSpellPriority(int32 NewPriority);

	UFUNCTION(BlueprintPure)
	int32 GetSpellPriority() const;
	
	UFUNCTION(BlueprintPure)
	UAnimMontage* GetPlayingMontage() const;

	UFUNCTION(BlueprintPure)
	bool CheckTargetAttitude(ACombatant* Target);


	// ----------------------- 继承接口实现 ----------------------------
	/**
	 * @brief 响应技能事件
	 * @param CombatEvent 技能事件实例
	 */
	virtual void HandleCombatEvent(const class UCombatEvent* CombatEvent) override;
protected:
	
	// ----------------------- Montage回调接口 ----------------------------
public:
	// >>>>>>>>>> Montage Notify
	void HandleSpellMontageStart(UCombatTask_SpellPlayMontage* MontageTask);
	void HandleSpellMontageFinished(const UCombatTask_SpellPlayMontage* MontageTask);
	void HandleSpellMontageNotify(const USpellMontageNotify* MontageNotify);
	// >>>>>>>>>> Anim State
	void HandleSpellAnimStateNotifyBegin(USpellNotifyStateInst* SpellNotifyStateInst);
	void HandleSpellAnimStateNotifyEnd(USpellNotifyStateInst* SpellNotifyStateInst);
	UFUNCTION(BlueprintImplementableEvent)
	void OnSpellAnimStateNotifyBegin(const USpellNotifyStateInst* SpellNotifyStateInst);
	UFUNCTION(BlueprintImplementableEvent)
	void OnSpellAnimStateNotifyEnd(const USpellNotifyStateInst* SpellNotifyStateInst);

	USpellNotifyStateInst* GetSpellNotifyStateInst(USpellNotifyState* State);

	/**
	 * @brief 获取战斗任务组件
	 * @param Task 当前任务
	 * @return 任务组件
	 */
	virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;
	virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;

	// >>>>>>>>>>> ICombatEffectOwnerInterface
	virtual FName GetDisplayName() override;
	virtual ACombatant* GetOwnerCombatant() override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void CastStart();
	/**
	 * @brief 技能释放开始
	 */
	UFUNCTION(BlueprintCallable)
	void OnSpellCastStart();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnSpellCastStart"))
    void BP_OnSpellCastStart();
	/**
	 * @brief 技能释放成功
	 */
	UFUNCTION(BlueprintCallable)
	void CastSuccess();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnSpellCastSuccess"))
	void BP_OnSpellCastSuccess();
	/**
	* @brief 技能释放完成
	*/
	UFUNCTION(BlueprintCallable)
	void CastFinished(const FGameplayTag Code);
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnSpellCastFinished"))
	void BP_OnSpellCastFinished(const FGameplayTag Code);

	void OnSpellCharged();
	
	/**
	 * @brief 技能在目标身上应用
	 * @param CombatEffect 技能效果
	 * @param Target 目标
	 */
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnSpellEffectApplied"))
	void BP_OnSpellEffectApplied(UCombatEffect* CombatEffect, ACombatant* Target);

	// ----------------------- 技能效果接口 ----------------------------
	virtual FCombatEffectContainerSpec* FindEffectContainerSpec(const FName Key) override;
	virtual TMap<FName, UCombatEffect*>& GetEffectContainer() override;
	virtual TMap<FName, UCombatTargetType*>& GetTargetBuilderContainer() override;
	virtual FGameplayTagContainer& GetEffectParentTags() override;
	
	
	void ApplyGameplayEffect(const FGameplayTag& Tag, TSoftObjectPtr<ACombatant> Target, UObject* ApplySpec);
	
	UFUNCTION(BlueprintCallable, meta=(DisplayName="ApplyGameplayEffect"))
	void BP_ApplyGameplayEffect(FGameplayTag Tag, TSoftObjectPtr<ACombatant> Target, UObject* ApplySpec);

	// ----------------------- 技能测试接口 ----------------------------
	UFUNCTION(BlueprintCallable)
	void SimulateMontageNotify(class UAnimMontage* SimMontage);

public:
	UFUNCTION(BlueprintPure)
	virtual FGameplayTagContainer& GetGameplayTagContainer() override;
	virtual void AddGameplayTag(const FGameplayTag& Tag) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddGameplayTag(const FName TagName) override;
	virtual void RemoveGameplayTag(const FGameplayTag& Tag, bool bDeferParentTags) override;
	UFUNCTION(BlueprintCallable)
	virtual void RemoveGameplayTag(const FName TagName, bool bDeferParentTags) override;
	virtual bool HasGameplayTag(const FGameplayTag& Tag, bool Exact) const override;
	UFUNCTION()
	virtual bool HasGameplayTag(const FName TagName, bool Exact) const override;
	UFUNCTION(BlueprintPure, meta=(DisplayName="HasGameplayTag"))
	virtual bool BP_HasGameplayTag(const FGameplayTag Tag, bool Exact) const override;
	virtual void PostGameplayTagChanged(const FGameplayTag Tag, bool bRemove) override;
	
	/**
	* @brief 技能取消时的广播事件
	*/
	FOnSpellCastCancelled OnSpellCastCancelled;	
protected:
	/**
	 * @brief 技能名称
	 */
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	FName SpellName;
	/**
	 * @brief 技能所属
	 */
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	ACombatant* SpellOwner;
	/**
	 * @brief 技能效果，通过Tag触发
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(ForceInlineRow), Category="SpellEffects")
	TMap<FGameplayTag, FCombatEffectContainerSpec> EffectContainer_Tag;
	/**
	* @brief 技能效果，手动触发
	*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(ForceInlineRow), Category="SpellEffects", AdvancedDisplay)
	TMap<FName, FCombatEffectContainerSpec> EffectContainer_Custom;
	/**
	 * @brief 释放技能时自动转向目标
	 */
	UPROPERTY(EditDefaultsOnly,Category="SpellTarget")
	bool LookAtTarget = false;
	/**
	* @brief 技能目标类型
	*/
	UPROPERTY(EditDefaultsOnly, Category = "SpellTarget", meta=(ForceInlineRow))
	FSpellTargetAttitude TargetAttitude;
	/**
	 * @brief 标识技能释放成功的Tag
	 */
	UPROPERTY(meta=(DeprecationMessage="not used"))
	FGameplayTag CastSuccessTag_DEPRECATED;
	/**
	* @brief 标识技能释放成功
	*/
	UPROPERTY(VisibleInstanceOnly)
	bool bCastSuccessful;
	/**
	 * @brief 技能是否有消耗
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle),Category="SpellCost")
	bool bSpellHasConsume = false;
	/**
	 * @brief 技能消耗
	 */
	UPROPERTY(EditDefaultsOnly, meta=(editcondition = "bSpellHasConsume"),Category="SpellCost")
	FSpellCost SpellCost;
	/**
	 * @brief 技能范围
	*/	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SpellRange")
	FFloatRange SpellRange;
	
	/**
	 * @brief 技能释放状态
	 */
	UPROPERTY(BlueprintReadWrite,VisibleInstanceOnly)
	ESpellState SpellState;
	/**
	 * @brief 技能优先级
	 */
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="SpellPriority")
	int32 SpellPriority = 0;
	/**
	 * @brief 技能权重
	 */
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="SpellWeight")
	int32 SpellWeight = 0;
	
public:
	/**
	 * @brief 技能充能
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle),Category="SpellCharge")
	bool bSpellHasCharge = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(editcondition = "bSpellHasCharge"),Category="SpellCharge")
	FSpellCharge SpellCharge;
	/**
	* @brief 技能冷却
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle),Category="SpellCooldown")
	bool bSpellHasCooldown = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(editcondition = "bSpellHasCooldown"),Category="SpellCooldown")
	FSpellCooldown SpellCooldown;
	/**
	* @brief 技能标签
	*/
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="SpellTags")
	FGameplayTagContainer SpellTags;
	/**
	 * @brief 技能释放参数
	 */
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FSpellCastParameter CastParameter;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	UAnimMontage* PlayingMontage;

	UPROPERTY(VisibleInstanceOnly)
	TWeakObjectPtr<UCombatTask_SpellPlayMontage> PlayMontageTask;

	UPROPERTY(VisibleInstanceOnly)
	TMap<FName, UCombatEffect*> EffectContainer;

	UPROPERTY(VisibleInstanceOnly)
	TMap<FName, UCombatTargetType*> TargetBuilderContainer;

public:
	UFUNCTION(CallInEditor)
	void DebugCast();
};