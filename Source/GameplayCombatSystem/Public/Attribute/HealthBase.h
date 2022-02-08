// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttributeBase.h"
#include "Combatant.h"
#include "UObject/NoExportTypes.h"
#include "HealthBase.generated.h"

/**
 * 生命值与护盾
 *	生命值与护盾耦合性比较大，且由于生命值与死亡等状态关联，所以区别于能量值单独作为特殊类
 *	生命值为单一数值，与能量值类似，只能加减，没有片段，有上限
 *	护盾作为生命值的扩充，具有片段的概念，支持多个技能/来源增加护盾
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UHealthBase : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 设置生命值所属
	 * @param InOwner 生命所属
	 */
	void SetHealthOwner(ACombatant* InOwner);
	/**
	 * @brief 受到伤害
	 * @param Damage 伤害值
	 * @param IgnoreShield 是否忽略护盾
	 */
	UFUNCTION(BlueprintCallable)
    void OnDamaged(float Damage, bool IgnoreShield=false);
	/**
	 * @brief 获得治疗
	 * @param Heal 治疗量
	 */
	UFUNCTION(BlueprintCallable)
    void OnHealed(float Heal);
	/**
	 * @brief 设置生命值
	 * @param NewHealth 生命值
	 */
	UFUNCTION(BlueprintCallable)
    void SetHealth(float NewHealth);
	// （是否包含护盾）
	/**
	 * @brief 获取生命值
	 * @param IncludeShield 是否包含护盾
	 * @return 生命值
	 */
	UFUNCTION(BlueprintPure)
    float GetHealth(bool IncludeShield=true);
	/**
	 * @brief 获取最大生命值
	 * @return 最大生命值
	 */
	UFUNCTION(BlueprintPure)
    float GetMaxHealth() const;
	/**
	 * @brief 获取护盾
	 * @return 护盾值
	 */
	UFUNCTION(BlueprintCallable)
    float GetShield();
	/**
	 * @brief 获取护盾片段数值
	 * @param Section 护盾片段
	 * @return 护盾值
	 */
	UFUNCTION(BlueprintCallable)
    float GetShieldSection(FName Section);
	/**
	 * @brief 应用护盾，会广播护盾增加事件
	 * @param Section 片段名称
	 * @param Value 护盾值
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyShield(FName Section, float Value);
	/**
	 * @brief 撤销护盾
	 * @param Section 护盾片段
	 */
	UFUNCTION(BlueprintCallable)
    void CancelShield(FName Section);
	/**
	 * @brief 设置取整策略
	 * @param NewPolicy 策略
	 */
	UFUNCTION(BlueprintCallable)
    void SetIntegerizationPolicy(EAttributeIntegerizationPolicy NewPolicy);
	
protected:
	/**
	 * @brief 设置护盾值
	 * @param Section 护盾片段
	 * @param NewValue 护盾值
	 */
	void SetShield(FName Section,float NewValue);

	/**
	 * @brief 生命值所属
	 */
	UPROPERTY(VisibleInstanceOnly)
	ACombatant* HealthOwner;

	/**
	 * @brief 当前生命值
	 */
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	float HealthValue;

	/**
	 * @brief 护盾抵挡伤害的顺序
	 */
	UPROPERTY(VisibleInstanceOnly)
	TArray<FName> SectionPriority;
	
	/**
	 * @brief 护盾片段值
	 */
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TMap<FName,float> ShieldSectionMap;
	
	/**
	* @brief 生命值受限配置
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bHasHealthLimit = false;
	UPROPERTY(EditDefaultsOnly, meta=(editcondition = "bHasHealthLimit"))
	FGameplayTag HealthLimitAttribute;
	
	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="整数化策略"))
	EAttributeIntegerizationPolicy IntegerizationPolicy = EAttributeIntegerizationPolicy::EAIP_TRUNCATE;
};
