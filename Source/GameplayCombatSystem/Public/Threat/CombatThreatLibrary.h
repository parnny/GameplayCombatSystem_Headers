// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatThreatLibrary.generated.h"

class ACombatant;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UCombatThreatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// UFUNCTION(BlueprintPure)
	// static bool QueryMostThreatenedSituation();
};
