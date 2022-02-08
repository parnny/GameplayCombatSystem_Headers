// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattlefieldSubsystem.h"
#include "BattlefieldActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API ABattlefieldActor : public AActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleInstanceOnly)
	TSoftObjectPtr<UBattlefield> Battlefield;
};
