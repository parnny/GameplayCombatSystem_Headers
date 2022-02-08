// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayCombatSortLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FSortVectorArrayDelegate, const FVector, A, const FVector, B);
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FSortObjectArrayDelegate, const UObject*, A, const UObject*, B);
/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UGameplayCombatSortLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void SortVectorArray(UPARAM(ref) TArray<FVector>& Array, FSortVectorArrayDelegate Delegate);

	UFUNCTION(BlueprintCallable)
	static void SortObjectArray(UPARAM(ref) TArray<UObject*>& Array, FSortObjectArrayDelegate Delegate);
};
