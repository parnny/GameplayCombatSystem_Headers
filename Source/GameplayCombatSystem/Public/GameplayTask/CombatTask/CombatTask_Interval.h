// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "CombatTask_Interval.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatTask_Interval : public UGameplayTask
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTaskDelayDelegate, int32, Times);

public:
	UCombatTask_Interval(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FTaskDelayDelegate OnFinish;
	UPROPERTY(BlueprintAssignable)
	FTaskDelayDelegate OnTick;

	virtual void Activate() override;

	/** Wait specified time. This is functionally the same as a standard Delay node. */
	UFUNCTION(BlueprintCallable, Category = "CombatTasks", meta = (DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "TRUE"))
	static UCombatTask_Interval* TaskTickInterval(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner, float Interval, int32 Times=-1);

	virtual void TickTask(float DeltaTime) override;
private:
	void OnTimeFinish();
	void OnTimeTick();
protected:
	virtual void OnDestroy(bool bInOwnerFinished) override;
private:
	float Interval;
	float Times;

	float Ticked;
	
	FTimerHandle TimerHandle;
};
