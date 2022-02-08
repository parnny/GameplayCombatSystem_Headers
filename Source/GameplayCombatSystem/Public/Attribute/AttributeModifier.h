// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttributeModifier.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UAttributeModifier : public UObject
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
