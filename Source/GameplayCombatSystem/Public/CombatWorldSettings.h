// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "CombatGlobalDefine.h"
#include "CombatWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API ACombatWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	/**
	 * @brief 重写基类 SetTimeDilation 函数，使得调用 UGameplayStatics::GetGlobalTimeDilation 写入新的变量[WorldTimeDilation]
	 * @param NewTimeDilation 
	 * @return 返回 Clamp处理的 NewTimeDilation
	 * 为什么不返回 FinalTimeDilation：在UGameplayStatics::GetGlobalTimeDilation中，返回与[NewTimeDilation]会有 Warning
	 */
	virtual float SetTimeDilation(float NewTimeDilation) override;
	
	virtual float SetCombatTimeDilation(float NewTimeDilation, ETimeDilationType DilationType);
	virtual void CancelCombatTimeDilation(ETimeDilationType DilationType);
	
	float GetCombatTimeDilation() const;
	
private:
	float UpdateFinalTimeDilation();
	
	//ETimeDilationType LastTimeDilationType = ETimeDilationType::ETDT_DEFAULT;
	//float CombatTimeDilation = 1.f;
	UPROPERTY()
	TMap<ETimeDilationType, float> CombatTimeDilation;

	/**
	 * @brief 替代基类的 TimeDilation
	 * Why: UGameplayStatics::GetGlobalTimeDilation直接访问[TimeDilation]变量，导致获取到的TimeDilation不包含CombatTimeDilation
	 */
	float WorldTimeDilation = 1.f;
};
