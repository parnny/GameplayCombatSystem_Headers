// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AuraPolicy.h"
#include "CombatEffect.h"
#include "CombatEventInterface.h"
#include "CombatTagInterface.h"
#include "GameplayTaskOwnerInterface.h"
#include "UObject/NoExportTypes.h"
#include "Combatant/Combatant.h"
#include "CombatWorldObject.h"
#include "Aura.generated.h"

/**
 * @brief 光环的生命周期类型
 */
UENUM(BlueprintType)
enum class EAuraLifetimeMode: uint8
{
	Lifetime_Infinite UMETA(DisplayName = "无限时间"),
	Lifetime_Finite UMETA(DisplayName = "有限时间"),
};

/**
 * 光环，增益效果与负面效果的统一
 * 来源于某个战斗单位附加给战斗单位（环境效果通常来源与目标是同一个）
 * 可以响应战斗事件 HandleCombatEvent
 * 包含各种战斗效果 CombatEffect
 *
 * 蓝图实现：
 *	BP_OnAuraActive 光环的具体效果
 *	BP_OnAuraTicked 光环时间改变时
 *	BP_OnAuraRemoved 光环移除效果
 *	BP_OnAuraDestroyed 光环销毁
 *	BP_HandleCombatEvent 对战斗事件的特殊处理
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UAura
	: public UCombatWorldObject
	, public ICombatEventInterface
	, public ICombatEffectInstigator
	, public IGameplayTaskOwnerInterface
	, public ICombatTagInterface
{
	GENERATED_BODY()

	friend UAuraComponent;
	
public:
	/**
	 * @brief 增加光环的入口, 会调用 OnAuraActive 与 OnAuraApplied
	 * @param InLifetime 光环时间
	 * @param InStack 光环层数
	 */
	void ApplyAura(float InLifetime=1.f, int32 InStack=1);

	/**
	 * @brief 刷新光环 只会调用 OnAuraActive 不会调用 OnAuraApplied
	 * @param NewLifetime 光环延长时间 
	 * @param NewStack 光环增加层数
	 */
	void RefreshAura(float NewLifetime=1.f, int32 NewStack=1);
	
	/**
	 * @brief 光环的Tick
	 * @param DeltaTime 时间变化 
	 */
	void TickAura(float DeltaTime);

	/**
	* @brief 移除光环，对光环反激活 OnAuraDeactivated ，调用 OnAuraRemoved
	 */
	void RemoveAura();

	/**
	 * @brief 光环销毁， 调用 OnAuraDestroyed
	 */
	void DestroyAura();
	/**
	 * @brief 判读光环可用，通常无限时间的光环判断层数，有限时间的同时判断层数和时间
	 * @return 是否可用
	 */
	bool IsAuraValid() const;

	/**
	 * @brief 获取光环ID
	 * @return 光环ID
	 */
	UFUNCTION(BlueprintPure)
	FName GetAuraID() const;

	// >>>>>>>>>> 光环的基本信息
	void SetAuraID(FName NewID);
	void SetAuraCreator(const ACombatant* Creator);
	void SetAuraOwner(const ACombatant* Owner);

	// 接受战斗事件
	virtual void HandleCombatEvent(const class UCombatEvent* CombatEvent) override;
	/**
	* @brief 获取战斗任务组件
	* @param Task 当前任务
	* @return 任务组件
	*/
	virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;

protected:
	// >>>>>>> 光环增加
	void OnAuraApplied();
	// >>>>>>> 光环激活
	void OnAuraActive(bool Refreshed=false);
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnAuraActive"))
    void BP_OnAuraActive(bool Refreshed);
	
	// >>>>>>> 光环Tick
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnAuraTicked"))
	void BP_OnAuraTicked(float DeltaTime);

	// >>>>>>> 光环移除
	void OnAuraRemoved();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnAuraRemoved"))
	void BP_OnAuraRemoved();

	// 光环销毁
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnAuraDestroyed"))
    void BP_OnAuraDestroyed();

	// 光环显示
	void OnAuraDisplayed(ACombatAvatar* Avatar);
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnAuraDisplayed"))
	void BP_OnAuraDisplayed(ACombatAvatar* Avatar);
	
	// 光环战斗事件
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="HandleCombatEvent"))
    void BP_HandleCombatEvent(const class UCombatEvent* CombatEvent);

	UFUNCTION(BlueprintCallable)
	void RemoveSelf();

	UFUNCTION(BlueprintCallable)
	void ClearTasks();
	
	virtual FCombatEffectContainerSpec* FindEffectContainerSpec(const FName Key) override;
	virtual TMap<FName, UCombatEffect*>& GetEffectContainer() override;
	virtual TMap<FName, UCombatTargetType*>& GetTargetBuilderContainer() override;
	virtual FGameplayTagContainer& GetEffectParentTags() override;
	
public:
	// >>>>>>>>>>>> ICombatEffectOwnerInterface
	virtual FName GetDisplayName() override;
	virtual ACombatant* GetOwnerCombatant() override;

	UFUNCTION(BlueprintCallable)
	bool ApplyTo(ACombatant* Combatant, UObject* NewApplySpec=nullptr);
	
	// 设置光环生命周期模式
	UFUNCTION(BlueprintCallable)
	void SetLifetimeMode(EAuraLifetimeMode Mode);
	// 光环生命周期
	UFUNCTION(BlueprintCallable)
	void SetLifetime(float InLifetime);
	UFUNCTION(BlueprintPure)
	float GetLifetime() const;
	// 光环层数
	UFUNCTION(BlueprintCallable)
	void SetStack(int32 InStack);
	UFUNCTION(BlueprintCallable)
	void RemoveStack(int32 DeltaStack=1);
	UFUNCTION(BlueprintCallable)
    void IncreaseStack(int32 DeltaStack=1);
	UFUNCTION(BlueprintPure)
	int32 GetStack() const;
	UFUNCTION(BlueprintPure)
    int32 GetMaxStack() const;
	
	// 光环事件的快速创建入口
	template<class EventType>
    EventType* CreateAuraEvent()
	{
		if (ACombatant* Broadcaster = AuraCreator.IsValid() ? AuraCreator.Get() : AuraOwner.Get())
		{
			return Broadcaster->CreateEvent<EventType>();
		}
		return nullptr;
	}

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
	virtual void PostGameplayTagChanged(const FGameplayTag Tag, bool bRemove) override {}
	

protected:
	/**
	 * @brief 光环ID
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FName AuraID;
	/**
	 * @brief 光环作用目标
	 */
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> AuraOwner;
	/**
	 * @brief 光环的创建者
	 */
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> AuraCreator;
	// 光环层数
	UPROPERTY(VisibleInstanceOnly)
	int32 AuraStack;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxStack=-1;
	// 光环生命周期类型
	UPROPERTY(EditDefaultsOnly)
	EAuraLifetimeMode AuraLifetimeMode;
	// 光环生命周期
	UPROPERTY(VisibleInstanceOnly)
	float AuraLifetime;
	UPROPERTY(EditDefaultsOnly)
	float MaxLifetime=-1;
	// 光环的自定义效果
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(ForceInlineRow), Category="AuraEffects")
	TMap<FName, FCombatEffectContainerSpec> EffectContainer_Custom;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(ForceInlineRow), Category="AuraEffects")
	TMap<FGameplayTag, FCombatEffectContainerSpec> EffectContainer_Tag;
	// 光环标签
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTagContainer AuraTags;
	/**
	 * @brief 是否使用自身的更新策略
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bOverrideRefreshPolicy = false;
	/**
	* @brief 光环的更新策略
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(editcondition = "bOverrideRefreshPolicy"))
	TSubclassOf<UAuraRefreshPolicy> RefreshPolicy;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bAuraTickable = true;

	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	bool bDisplayDirty = true;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UObject* ApplySpec;
	
	UPROPERTY(VisibleInstanceOnly)
	TMap<FName, UCombatEffect*> EffectContainer;

	UPROPERTY(VisibleInstanceOnly)
	TMap<FName, UCombatTargetType*> TargetBuilderContainer;
	
private:
	TSet<TSoftObjectPtr<UGameplayTask>> AuraTasks;
};

UCLASS()
class UAuraTagged : public UAura
{
	GENERATED_BODY()
public:
	UAuraTagged()
	{
		bAuraTickable = false;
	}
};
