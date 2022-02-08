// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnergyBase.h"
#include "CombatEvent/CombatEvent.h"
#include "CombatEventCombatant.generated.h"


/**
 * @brief 战斗单元事件
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatant : public UCombatEvent
{
	GENERATED_BODY()
public:
	UCombatEventCombatant()
        : Super()
	{
		EventCategory = "UNIT";
	}
};

/**
 * @brief 目标变化事件
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantRetarget : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UCombatEventCombatantRetarget()
	{
		EventName = "RETARGET";
	}
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> PreTarget;
};

/**
 * @brief 血量变化事件
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantHealth : public UCombatEventCombatant
{
	GENERATED_BODY()
	public:
	UCombatEventCombatantHealth()
	{
		EventName = "HEALTH";
	}
	UPROPERTY(BlueprintReadOnly)
	float PreHealth;
	UPROPERTY(BlueprintReadOnly)
	float NewHealth;

	virtual FString GetEventDesc() const
	{
		return FString::Format(TEXT("{0} -> {1}"), { PreHealth,NewHealth });
	}
};

/**
 * @brief 护盾事件
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantAppliedShield : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UCombatEventCombatantAppliedShield()
	{
		EventName = "APPLIED_SHIELD";
	}
	UPROPERTY(BlueprintReadOnly)
	float Shield;

	UPROPERTY(BlueprintReadOnly)
	FName Section;

	UPROPERTY(BlueprintReadOnly)
	float TotalShield;
};

/**
 * @brief 护盾取消事件
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantCancelShield : public UCombatEventCombatant
{
	GENERATED_BODY()
	public:
	UCombatEventCombatantCancelShield()
	{
		EventName = "CANCEL_SHIELD";
	}
	UPROPERTY(BlueprintReadOnly)
	FName Section;

	UPROPERTY(BlueprintReadOnly)
	float TotalShield;
};

/**
 * @brief 能量变化事件
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantEnergy : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UCombatEventCombatantEnergy()
	{
		EventName = "ENERGY";
	}
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag EnergyTag;
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UEnergyBase> Energy;
};


/**
* @brief 环境刺激事件，受刺激后根据情况决定是否受威胁
*/
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantStimulus : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> Instigator;
	UPROPERTY(BlueprintReadOnly)
	bool bStimulus;
	UCombatEventCombatantStimulus()
	{
		EventName = "STIMULUS";
	}
};

/**
* @brief 环境威胁列表更新事件
*/
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantThreatListUpdate : public UCombatEventCombatant
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintReadOnly)
	int32 ChangeCount;
	UCombatEventCombatantThreatListUpdate()
	{
		EventName = "THREAT_LIST_UPDATE";
		ChangeCount = 0;
	}
};

/**
* @brief 状态变化事件 
*/
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantStatusChanged : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UCombatEventCombatantStatusChanged()
	{
		EventName = "COMBAT_STATUS_CHANGED";
	}
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag StatusTag;

	UPROPERTY(BlueprintReadOnly)
	bool bInStatus;
};

/**
* @brief 标签变化事件 
*/
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantTagChanged : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UCombatEventCombatantTagChanged()
	{
		EventName = "COMBAT_TAGS_CHANGED";
	}
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag CombatantTag;

	UPROPERTY(BlueprintReadOnly)
	bool bRemove;
};

/**
* @brief 属性变化
*/
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantAttribute : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UCombatEventCombatantAttribute()
	{
		EventName = "ATTRIBUTE";
	}
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(BlueprintReadOnly)
	class UAttributeBase* Attribute;
};

/**
* @brief 绑定avatar
*/
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCombatantBindAvatar : public UCombatEventCombatant
{
	GENERATED_BODY()
public:
	UCombatEventCombatantBindAvatar()
	{
		EventName = "BIND_AVATAR";
	}
};