// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UWeaponInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API IWeaponInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	AActor* GetWeaponActor(FName WeaponSocket);
};
