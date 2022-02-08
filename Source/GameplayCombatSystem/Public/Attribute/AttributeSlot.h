// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSlot.generated.h"

/**
 * 属性插槽，具有多个数值片段
 * 定义每个片段的计算方式
 * 记录，撤销属性片段
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UAttributeSlot : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	float GetFloatValue();

	UFUNCTION(BlueprintCallable)
	void ApplyModify(FName Source, float Value);

	UFUNCTION(BlueprintCallable)
	void CancelModify(FName Source);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TMap<FName, float> InnerValues;
};
