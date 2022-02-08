// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "CombatEvent.generated.h"

class ACombatant;
/**
 * @brief 战斗事件定义
 */
struct GAMEPLAYCOMBATSYSTEM_API FCombatDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FCombatEventDelegate, const class UCombatEvent*);
	static FCombatEventDelegate CombatEventDelegate;
};

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UCombatEvent : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	FName SubHandleFuncName = NAME_None;
	/**
	 * @brief 事件的时间戳
	 */
	int64 Timestamp;
	/**
	 * @brief 创建事件的战斗单元
	 */
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> SrcCombatant;

	/**
	* @brief 广播的目标
	*/
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> DesCombatant;
	
	/**
	 * @brief 获取事件名称
	 * @return 事件名称
	 */
	UFUNCTION(BlueprintPure)
	virtual FString GetEventName() const
	{
		return FString::Printf(TEXT("%s_%s"),*EventCategory,*EventName);
	}
	
	UFUNCTION(BlueprintPure)
	virtual FString GetEventDesc() const
	{
		return "";
	}
	/**
	 * @brief 打印字符串
	 * @return 字符串
	 */
	UFUNCTION(BlueprintPure)
	FString ToString() const
	{
		return FString::Format(TEXT("[{0}]:{1}"),{GetEventName(),GetEventDesc()});
	}

	/**
	 * @brief 广播事件
	 * @param TargetCombatant 广播对象
	 */
	UFUNCTION(BlueprintCallable)
	void Broadcast(ACombatant* TargetCombatant=nullptr);
	
protected:
	/**
	 * @brief 事件分类
	 */
	UPROPERTY(EditDefaultsOnly)
	FString EventCategory;
	/**
	 * @brief 事件名称
	 */
	UPROPERTY(EditDefaultsOnly)
	FString EventName;
};


/**
 * @brief 自定义事件
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UCombatEventCustom : public UCombatEvent
{
	GENERATED_BODY()
public:
	/**
	 * @brief 事件标签
	 */
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FGameplayTag EventTag;
};