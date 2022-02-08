// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "CombatTask_Slomo.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatTask_Slomo : public UGameplayTask
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskSlomoDelegate);

public:
	UCombatTask_Slomo(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FTaskSlomoDelegate OnFinish;

	virtual void Activate() override;

	/** Wait specified time. This is functionally the same as a standard Delay node. */
	UFUNCTION(BlueprintCallable, Category = "CombatTasks", meta = (DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "TRUE"))
	static UCombatTask_Slomo* TaskSlomo(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner, float TimeDilation, float Duration=1.f,bool UsingRealDuration=false);

	virtual void TickTask(float DeltaTime) override;
	
private:
	void OnSlomoFinish();

	float Duration;
	float TimeDilation;
	bool bRealDuration;
	float TimeSeconds;
};
