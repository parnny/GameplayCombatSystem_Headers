// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LandmarkInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable,BlueprintType)
class ULandmarkInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API ILandmarkInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent)
	FName GetLandmarkName();
};
