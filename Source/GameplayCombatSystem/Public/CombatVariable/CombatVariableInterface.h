// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CombatVariable.h"
#include "UObject/Interface.h"
#include "CombatVariableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatVariableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API ICombatVariableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};

UCLASS()
class UCombatVariableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, meta=(CompactNodeTitle = "Get"))
	static float GetValue(FCombatVariable_Float CV, TScriptInterface<ICombatVariableInterface> Env);
};

//
// /** Adds a float to each component of a vector */
// UFUNCTION(BlueprintPure, meta=(DisplayName = "vector + float", CompactNodeTitle = "+", ScriptMethod = "AddFloat", Keywords = "+ add plus"), Category="Math|Vector")
// static FVector Add_VectorFloat(FVector A, float B);