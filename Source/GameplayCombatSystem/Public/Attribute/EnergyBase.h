// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "AttributeDefines.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "EnergyBase.generated.h"

/**
 * 能量值
 * 作为技能等消耗值存在
 * 能量值的特点:
 *	单一数值，只有增加消耗，没有片段概念，无法撤销修改
 *	一般来说会有上限，上限取决于属性
 *	即时制战斗可能会有每秒增长的概念
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UEnergyBase : public UObject
{
	GENERATED_BODY()
public:
	// 能量值的基本信息
	void SetEnergyOwner(class ACombatant* InOwner);
	void SetEnergyTag(FGameplayTag& NewTag);
	// 设置能量值
	UFUNCTION(BlueprintCallable)
	void SetEnergy(float InValue);
	// 修改能量值
	UFUNCTION(BlueprintCallable)
    void ChangeEnergy(float DeltaValue);
	// 获取能量值
	UFUNCTION(BlueprintPure)
	float GetEnergy() const;
	// 是否最大能量
	UFUNCTION(BlueprintPure)
	bool IsMaxEnergy() const;
	UFUNCTION(BlueprintPure)
	float GetMaxEnergy() const;
	/**
	* @brief 设置取整策略
	* @param NewPolicy 策略
	*/
	UFUNCTION(BlueprintCallable)
    void SetIntegerizationPolicy(EAttributeIntegerizationPolicy NewPolicy);
	
protected:
	// 能量值
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	float EnergyValue;

	// 所属
	UPROPERTY(VisibleInstanceOnly)
	class ACombatant* EnergyOwner;
	
	UPROPERTY(VisibleInstanceOnly)
	FGameplayTag EnergyTag;

	// 能量值受限配置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bHasEnergyLimit = false;
	UPROPERTY(EditDefaultsOnly, meta=(editcondition = "bHasEnergyLimit"))
	FGameplayTag EnergyLimitAttribute;
	
	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="整数化策略"))
	EAttributeIntegerizationPolicy IntegerizationPolicy = EAttributeIntegerizationPolicy::EAIP_TRUNCATE;
};
