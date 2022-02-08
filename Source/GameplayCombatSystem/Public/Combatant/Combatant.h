// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatEvent.h"
#include "CombatEventInterface.h"
#include "CombatAvatar.h"
#include "BattlefieldLandmark.h"
#include "CombatEffectInstigator.h"
#include "CombatGlobalDefine.h"
#include "CombatTagInterface.h"
#include "WeakInterfacePtr.h"
#include "GameFramework/Character.h"
#include "Combatant.generated.h"

class ABattlefield;

/**
 * @brief 战斗单位
 * 战斗组件:
 *	SpellComponent 技能
 *	AuraComponent 光环
 *	AttributeComponent 属性
 *	CombatTaskComponent 异步任务
 */
UCLASS(Blueprintable,BlueprintType, HideCategories=(Transfrom,Animation,Mesh,Tags))
class GAMEPLAYCOMBATSYSTEM_API ACombatant : public AActor, public ICombatEventInterface, public ICombatTagInterface, public ICombatTeamAgentInterface
{
	GENERATED_UCLASS_BODY()

	/** Called after all the components in the Components array are registered, called both in editor and during gameplay */
    virtual void PostRegisterAllComponents() override;
	virtual void PostUnregisterAllComponents() override;

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Destroyed() override;
	
public:
	/**
	 * @brief 接收作用于自己的战斗效果
	 * @param CombatEffect 战斗效果
	 */
	void HandleCombatEffect(class UCombatEffect* CombatEffect);
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "HandleCombatEffect"))
	void BP_HandleCombatEffect(class UCombatEffect* CombatEffect);

	/**
	 * @brief 战斗单元死亡
	 */
	void OnCombatantDead();

	// >>>>>>>>>>>>>>>>>> ICombatEventInterface
	virtual void HandleCombatEvent(const UCombatEvent* CombatEvent) override;

	/**
	 * @brief 设置战斗单元名称
	 * @param NewName 设置名称
	 */
	UFUNCTION(BlueprintCallable)
	void SetCombatantName(FName NewName);
	UFUNCTION(BlueprintPure)
	FName GetCombatantName() const;

	/**
	 * @brief 是否可以被选中，默认实现只判断死亡状态
	 * @return 
	 */
	UFUNCTION(BlueprintPure,BlueprintNativeEvent)
	bool IsTargetable() const;

	/**
	 * @brief 获取当前目标
	 * @return 当前目标
	 */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	ACombatant* GetTarget() const;
	/**
	 * @brief 设置目标
	 * @param CombatantTarget 新目标
	 */
	UFUNCTION(BlueprintCallable)
	void SetTarget(const ACombatant* CombatantTarget);

	/**
	 * @brief 设置表现用的Avatar
	 * @param NewAvatar 
	 */
	UFUNCTION(BlueprintCallable)
	void SetAvatar(ACombatAvatar* NewAvatar);
	/**
	 * @brief 获取表现用的Avatar
	 * @return 当的的Avatar
	 */
	UFUNCTION(BlueprintPure)
	ACombatAvatar* GetAvatar() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAvatarSetup(ACombatAvatar* NewAvatar);

	/**
	 * @brief 判断死亡状态
	 * @return 是否存活
	 */
	UFUNCTION(BlueprintPure)
    bool IsAlive() const;

	/**
	 * @brief 根据事件类型创建实例
	 * @param EventClass 事件类型
	 * @return 事件实例
	 */
	UFUNCTION(BlueprintPure)
	UCombatEvent* CreateEvent(TSubclassOf<UCombatEvent> EventClass);

	/**
	 * @brief 通过模板创建实例
	 * @tparam EventType 事件类型
	 * @return 事件实例
	 */
	template<class EventType>
	EventType* CreateEvent()
	{
		if (EventType* Object = NewObject<EventType>(this))
		{
			if (UCombatEvent* Event = Cast<UCombatEvent>(Object))
			{
				const FDateTime Time = FDateTime::Now();
				Event->SrcCombatant = this;
				Event->Timestamp = Time.ToUnixTimestamp();
				return Object;
			}
		}
		return nullptr;
	}

	// >>>>>>>>>> 组件获取
	UFUNCTION()
	class USpellComponent* GetSpellComponent() const;
	UFUNCTION()
	class UAuraComponent* GetAuraComponent() const;
	UFUNCTION()
	class UAttributeStatsComponent* GetAttributeComponent() const;
	UFUNCTION()
	class UThreatComponent* GetThreatComponent() const;
	UFUNCTION()
	class UCombatStatusComponent* GetStatusComponent() const;
	// 任务组件不开放给脚本,所以没有UFCUNTION修饰
	class UGameplayTasksComponent* GetCombatTaskComponent() const;

	UFUNCTION(BlueprintCallable)
	bool TestEntry(UPARAM(ref) FVector& RefVector,FVector Vector, FVector& OutVector);

	UFUNCTION(BlueprintCallable)
	AActor* SpawnCreature(TSubclassOf<AActor> CreatureClass, TScriptInterface<ICombatEffectInstigator> EffectInstigator);
	
	UFUNCTION()
	void OnCreatureDestroyed(AActor* DestroyedActor);
	
	UFUNCTION(BlueprintCallable)
	AActor* SpawnSubActor(TSubclassOf<AActor> ActorClass);
	
	// IGenericTeamAgentInterface
	UFUNCTION(BlueprintCallable)
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	UFUNCTION(BlueprintPure)
	virtual FGenericTeamId GetGenericTeamId() const override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "HandleCombatEvent"))
    void BP_HandleCombatEvent(const class UCombatEvent* CombatEvent);

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


	UFUNCTION(BlueprintPure)
	FVector ExtractCombatLocation(FCombatLocation CombatLocation, bool Navigable=true, bool IncludeAvatar=true) const;
public:
	/**
	 * @brief 地标
	 */
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	ULandmarkContainer* Landmarks;

protected:
	/**
	 * @brief 战斗单元名称
	 */
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	FName CombatantName;

	/**
	 * @brief 目标
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<ACombatant> TargetCombatant;

	/**
	 * @brief Avatar
	 */
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	ACombatAvatar* Avatar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag TeamAttitudeTag;
	
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	FGenericTeamId GenericTeamId = FGenericTeamId::NoTeam;
	
	/**
	 * @brief 战斗单元标签
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer CombatantTags;
	
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class USpellComponent* SpellComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UAuraComponent* AuraComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UAttributeStatsComponent* AttributeComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UThreatComponent* ThreatComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UCombatStatusComponent* StatusComponent;
	
	UPROPERTY()
	class UCombatTaskComponent* CombatTaskComponent;
	
	UPROPERTY(VisibleInstanceOnly)
	TSet<AActor*> SpawnedCreatures;
	
	TArray<TWeakInterfacePtr<ICombatEventInterface>> CombatEventHandlers;
};
