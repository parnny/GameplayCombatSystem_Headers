// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "UObject/NoExportTypes.h"
#include "SpellContext.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API USpellContext : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TSoftObjectPtr<ACombatant> Target;
};
