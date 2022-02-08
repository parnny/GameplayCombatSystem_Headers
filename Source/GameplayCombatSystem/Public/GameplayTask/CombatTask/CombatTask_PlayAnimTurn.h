// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatAvatar.h"
#include "GameplayTask.h"
#include "CombatTask_PlayAnimTurn.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatTask_PlayAnimTurn : public UGameplayTask
{
	GENERATED_UCLASS_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCombatTaskPlayAnimTurnEnd);

	virtual void Activate() override;

	/** Wait specified time. This is functionally the same as a standard Delay node. */
	UFUNCTION(BlueprintCallable, Category = "GameplayTasks",
		meta = (DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "TRUE"))
	static UCombatTask_PlayAnimTurn* PlayAnimTurn(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner,
	                                              ACombatAvatar* Avatar, UAnimMontage* Montage, FName CurveName,
	                                              float Scale, int32 Priority, float InPlayRate = 1.f,
	                                              FName StartSection = NAME_None);
	
	virtual void TickTask(float DeltaTime) override;

protected:
	virtual void OnDestroy(bool bInOwnerFinished) override;
	bool IsTaskValid() const;

	UPROPERTY(BlueprintAssignable)
	FCombatTaskPlayAnimTurnEnd OnFinished;
	
	UPROPERTY()
	TSoftObjectPtr<ACombatAvatar> Avatar;

	UPROPERTY()
	TSoftObjectPtr<UAnimMontage> Montage;

	FName CurveName;
	float Scale;
	int32 Priority;
	float PlayRate = 1.f;
	FName StartSection = NAME_None;

	float CurveValue;
};
