// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattlefieldActor.h"
#include "GenericTeamAgentInterface.h"
#include "CombatSystemSettings.generated.h"

/**
 * 
 */
UCLASS(config=CombatSystem, defaultconfig)
class GAMEPLAYCOMBATSYSTEM_API UCombatSystemSettings : public UObject
{
	GENERATED_BODY()
public:
    static ETeamAttitude::Type GetTeamAttitudeTowards(FGenericTeamId TeamA, FGenericTeamId TeamB);

	UPROPERTY(config, EditAnywhere, Category = "AttitudeTowards",meta=(ForceInlineRow))
	TMap<FIntPoint, TEnumAsByte<ETeamAttitude::Type>> AttitudeTowards;
	
	UPROPERTY(config, EditAnywhere)
	TSubclassOf<ABattlefieldActor> BattlefieldClass;
};
