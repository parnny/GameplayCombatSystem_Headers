// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatTargetType.generated.h"

class ACombatant;
/**
 * 目标选择类型
 * 具体选择逻辑在蓝图中扩展
 * 不需要直接实例化，请使用CDO
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UCombatTargetType : public UObject
{
	GENERATED_BODY()
	
public:
	UCombatTargetType(){}

	/**
	 * @brief 构建目标列表
	 * @param Combatant 选择目标的人
	 * @param Instigator 发起源, 可能是技能，也可能是光环
	 * @param RawTarget 原始目标
	 * @param OutTargets 目标列表
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void GetTargets(ACombatant* Combatant, UObject* Instigator,ACombatant* RawTarget, TArray<ACombatant*>& OutTargets) const;
};