// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttributeDefines.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "AttributeBase.generated.h"

/**
 * 属性基类
 * 作用于：攻击力，防御力，最大血量(非当前血量)
 * 功能：
 *	- 定义了该属性的Slot的数量，每个slot为一个计算因子
 *  - 定义了该属性的计算方式
 *  - 修改每个Slot的数据
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UAttributeBase : public UObject
{
	GENERATED_BODY()

	friend class UAttributeStatsComponent;

public:
	// 创建属性插槽
	void Init(const FGameplayTag& Tag);
	// 设置属性所属
	void SetAttributeOwner(class ACombatant* InOwner);
	
	// 获取属性数值
	UFUNCTION(BlueprintPure)
	float GetValue();

	// 修改属性数值
	UFUNCTION(BlueprintCallable)
	void ApplyModify(FName SlotName,FName Source, float Value);

	// 撤销对属性数值的修改
	UFUNCTION(BlueprintCallable)
	void CancelModify(FName SlotName,FName Source);
	/**
	* @brief 设置取整策略
	* @param NewPolicy 策略
	*/
	UFUNCTION(BlueprintCallable)
	void SetIntegerizationPolicy(EAttributeIntegerizationPolicy NewPolicy);

protected:
	// 计算属性接口，蓝图实现
	UFUNCTION(BlueprintImplementableEvent)
	float CalculateValue();

	// 获取某个插槽的数值
	UFUNCTION(BlueprintPure)
	float GetSlotValue(FName SlotName);
	
public:
	// 定义插槽类型
	UPROPERTY(EditDefaultsOnly)
	TMap<FName,TSubclassOf<class UAttributeSlot>> ModifierClasses;
	
	// 调试接口，重新计算属性
	UFUNCTION(CallInEditor)
	void ReCalculateValue();

protected:
	// 插槽实例
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TMap<FName, class UAttributeSlot*> ModifierSlots;

	// 属性归属
	UPROPERTY(VisibleInstanceOnly)
	class ACombatant* AttributeOwner;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FGameplayTag AttributeTag;

	// 当前数值缓存
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	float FinalValue;

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="整数化策略"))
	EAttributeIntegerizationPolicy IntegerizationPolicy = EAttributeIntegerizationPolicy::EAIP_TRUNCATE;
private:
	// 属性标记
	bool MaskDirty;
};