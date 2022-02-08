// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "UObject/Interface.h"
#include "CombatTeamAgentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType,meta = (CannotImplementInterfaceInBlueprint))
class UCombatTeamAgentInterface : public UGenericTeamAgentInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API ICombatTeamAgentInterface : public IGenericTeamAgentInterface
{
	GENERATED_IINTERFACE_BODY()
};
