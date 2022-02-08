// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "ThreatSituation.generated.h"


UENUM()
enum class EThreadModifyReason : uint8
{
	ETMP_UNKNOWN UMETA(DisplayName = "未知"),
	ETMP_ENTERCOMBAT UMETA(DisplayName = "进战初始化"),
	ETMP_INTERVALREDUCE UMETA(DisplayName = "定时衰减"),
	ETMP_HOSTILE_DEAD UMETA(DisplayName = "敌对方死亡"),
	ETMP_HOSTILE_SWITCHMASTER UMETA(DisplayName = "敌对方切换主控"),
	ETMP_DAMAGED UMETA(DisplayName = "受到伤害"),
};

USTRUCT(BlueprintType)
struct FThreatSituation
{
	GENERATED_BODY()

	FThreatSituation& operator=(const FThreatSituation* ThreatSituation);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float RawThreatValue;	

	// 仇恨值最近修改时间
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 LastModifyTime;
		
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap< EThreadModifyReason, int32 > LastModifyTimeByReason;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ThreatValue;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsValid = false;
};