// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeBase.h"
#include "EnergyBase.h"
#include "Combatant/CombatantComponent.h"
#include "HealthBase.h"
#include "AttributeStatsComponent.generated.h"

#define INVALID_ATTRIBUTE -1.f;
/*
 * 属性组件
 *	管理战斗属性，战斗能量资源，玩家血量
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCOMBATSYSTEM_API UAttributeStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeStatsComponent();

	// 初始化组件
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// ------------------------- 战斗能量资源 ---------------------
	// 改变能量值
	void ChangeEnergy(const FGameplayTag& EnergyTag, float EnergyDelta);
	UFUNCTION(Category = "Energy")
	void ChangeEnergy(const FName EnergyName, float EnergyDelta);
	UFUNCTION(BlueprintCallable, Category="Energy", meta=(DisplayName = "ChangeEnergy"),meta=(GameplayTagFilter="Combat.Energy"))
    void BP_ChangeEnergy(const FGameplayTag EnergyTag, float EnergyDelta);
	// 设置能量值
	void SetEnergy(const FGameplayTag& EnergyTag, float EnergyValue);
	UFUNCTION(Category = "Energy")
	void SetEnergy(const FName EnergyName, float EnergyValue);
	UFUNCTION(BlueprintCallable, Category="Energy", meta=(DisplayName = "SetEnergy"),meta=(GameplayTagFilter="Combat.Energy"))
    void BP_SetEnergy(const FGameplayTag EnergyTag, float EnergyValue);
	// 获取能量值
	float GetEnergy(const FGameplayTag& EnergyTag);
	UFUNCTION(Category = "Energy")
	float GetEnergy(const FName EnergyName);
	UFUNCTION(BlueprintPure, Category = "Energy", meta=(DisplayName = "GetEnergy"),meta=(GameplayTagFilter="Combat.Energy"))
	float BP_GetEnergy(const FGameplayTag EnergyTag);
	// 获取能量对象
	UEnergyBase* FindEnergy(const FGameplayTag& EnergyTag);
	UFUNCTION(Category = "Energy")
	UEnergyBase* FindEnergy(const FName EnergyName);
	UFUNCTION(BlueprintPure, Category = "Energy", meta=(DisplayName = "GetEnergy"),meta=(GameplayTagFilter="Combat.Energy"))
	UEnergyBase* BP_FindEnergy(const FGameplayTag EnergyTag);

	
	// ------------------------- 生命值管理 ---------------------
	// 受到伤害
	UFUNCTION(BlueprintCallable, Category = "Health")
    void OnDamaged(float Damage, bool bCritical, bool bIgnoreShield, UCombatEffect* Effect, FGameplayTagContainer& Tags);
	// 受到治疗
	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnHealed(float Heal);
	// 设置生命值
	UFUNCTION(BlueprintCallable)
    void SetHealth(float NewHealth);
	// 获取生命值
	UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealth(bool IncludeShield=true);
	// 获取护盾
	UFUNCTION(BlueprintPure, Category = "Health")
    float GetShield();
	// 获取护盾片段
	UFUNCTION(BlueprintPure, Category = "Health")
    float GetShieldSection(FName Section);
	// 附加护盾
	UFUNCTION(BlueprintCallable, Category = "Health")
    void ApplyShield(FName Section, float Value);
	// 取消护盾片段
	UFUNCTION(BlueprintCallable, Category = "Health")
    void CancelShield(FName Section);

	// 注册属性
	UFUNCTION(Category = "Attribute", meta=(DisplayName = "ModifyAttribute"))
    void RegisterAttribute(FName AttributeName, TSubclassOf<UAttributeBase> AttributeClass);
	// 修改属性
	UFUNCTION(BlueprintCallable, Category = "Attribute", meta=(DisplayName = "ModifyAttribute", GameplayTagFilter="Combat.Attribute"))
    void ModifyAttribute(const FGameplayTag AttributeTag, FName SlotName = "Default", FName Source = "Unknown", float Value = 0.f);
	// 撤销属性修改
	UFUNCTION(BlueprintCallable, Category = "Attribute", meta=(DisplayName = "CancelModify", GameplayTagFilter="Combat.Attribute"))
    void CancelModify(const FGameplayTag AttributeTag, FName SlotName = "Default", FName Source = "Unknown");
	// 获取属性
	UFUNCTION(BlueprintPure, Category = "Attribute", meta=(DisplayName = "GetAttribute", GameplayTagFilter="Combat.Attribute"))
    float GetAttribute(const FGameplayTag AttributeTag);

	/**
	* @brief 设置取整策略
	* @param NewPolicy 策略
	*/
	UFUNCTION(BlueprintCallable)
    void SetIntegerizationPolicy(EAttributeIntegerizationPolicy NewPolicy);


	void BroadcastAttributeEvent(UAttributeBase* Attribute) const;
	

protected:
	// 生命值
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHealthBase> HealthClasses;
	UPROPERTY(VisibleInstanceOnly)
	UHealthBase* Health;

	// 能量值
	UPROPERTY(EditDefaultsOnly,meta=(ForceInlineRow))
	TMap<FGameplayTag,TSubclassOf<UEnergyBase>> EnergyClasses;
	UPROPERTY(VisibleInstanceOnly, meta=(ForceInlineRow))
	TMap<FGameplayTag, UEnergyBase*> EnergyMap;

	// 属性配置
	UPROPERTY(EditDefaultsOnly,meta=(ForceInlineRow))
	TMap<FGameplayTag, TSubclassOf<UAttributeBase>> AttributeClasses;
	UPROPERTY(VisibleInstanceOnly,meta=(ForceInlineRow))
	TMap<FGameplayTag, UAttributeBase*> AttributeMap;

	// 组件所属
	UPROPERTY(BlueprintReadOnly)
	ACombatant* AttributeOwner;
};
