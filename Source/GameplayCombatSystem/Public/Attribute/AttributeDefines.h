// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeDefines.generated.h"

UENUM()
enum class EAttributeIntegerizationPolicy : uint8
{
	EAIP_KEEP UMETA(DisplayName = "不取整"),
	EAIP_TRUNCATE UMETA(DisplayName = "保留整数位",  Tooltips="-1.6 becomes -1 and 1.6 becomes 1"),
	EAIP_ROUND UMETA(DisplayName = "四舍五入", Tooltips="-1.6 becomes -2 and 1.6 becomes 2"),
	EAIP_FLOOR UMETA(DisplayName = "向下取整", Tooltips="-1.6 becomes -2 and 1.6 becomes 1"),
	EAIP_CEIL UMETA(DisplayName = "向下取整", Tooltips="-1.6 becomes -1 and 1.6 becomes 2"),
};

struct GAMEPLAYCOMBATSYSTEM_API FAttributeIntegerization
{
	static float Integerization(float InValue, EAttributeIntegerizationPolicy Policy=EAttributeIntegerizationPolicy::EAIP_TRUNCATE)
	{
		switch (Policy)
		{
			case EAttributeIntegerizationPolicy::EAIP_TRUNCATE:
				return  FMath::TruncToFloat(InValue);
			case EAttributeIntegerizationPolicy::EAIP_ROUND:
				return  FMath::RoundToFloat(InValue);
			case EAttributeIntegerizationPolicy::EAIP_FLOOR:
				return  FMath::FloorToFloat(InValue);
			case EAttributeIntegerizationPolicy::EAIP_CEIL:
				return  FMath::CeilToFloat(InValue);
			case EAttributeIntegerizationPolicy::EAIP_KEEP: break;
			default: ;
		}
		return  FMath::TruncToFloat(InValue);
	}
};