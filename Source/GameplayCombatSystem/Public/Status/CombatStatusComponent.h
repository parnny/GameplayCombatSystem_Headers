// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CombatStatusComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCOMBATSYSTEM_API UCombatStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable,meta=(GameplayTagFilter="Combat.Status"))
	void SetCombatStatus(const FGameplayTag StatusTag, const bool InState);
	
	UFUNCTION(BlueprintCallable)
	void ClearCombatStatus(const FGameplayTag StatusTag);

	UFUNCTION(BlueprintPure)
	bool IsInCombatStatus(const FGameplayTag StatusTag);

	UFUNCTION(BlueprintPure)
	void GetCombatStatus(FGameplayTagContainer& GameplayTags);
	
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, int32> CombatStatus;

	void BroadcastThreatEvent(const FGameplayTag& StatusTag);

	UFUNCTION(BlueprintCallable)
	void SetStatusTimeLock(const FName LockName, const float Duration);

	UFUNCTION(BlueprintPure)
	bool HasStatusTimeLock(const FName LockName);
	
	UPROPERTY(EditAnywhere)
	TMap<FName, float> StatusTimeLock;
};
