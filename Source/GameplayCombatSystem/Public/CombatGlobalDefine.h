// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "UObject/NoExportTypes.h"
#include "CombatGlobalDefine.generated.h"

USTRUCT(BlueprintType)
struct FCombatLocation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(editcondition = "!bUsingLandmark"))
	FVector Offset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(editcondition = "bUsingLandmark"))
	FName Landmark;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bUsingLandmark = false;
};


UENUM(BlueprintType)
enum class ETimeDilationType : uint8
{
	ETDT_DEFAULT,
	ETDT_HIT,
	ETDT_BURST,
	ETDT_CAMERA,
	ETDT_UI,
	ETDT_MAX,
};

USTRUCT(BlueprintType)
struct FCombatantAttitudeFilter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bFriendly = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bNeutral = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHostile = true;

	bool IsAttitudeValid(const ETeamAttitude::Type TeamAttitude) const
	{
		switch (TeamAttitude)
		{
		case ETeamAttitude::Friendly:
			return bFriendly;
		case ETeamAttitude::Neutral:
			return bNeutral;
		case ETeamAttitude::Hostile:
			return bHostile;
		}
		return false;
	}
};