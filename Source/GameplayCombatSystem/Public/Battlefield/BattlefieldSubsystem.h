// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "BattlefieldSubsystem.generated.h"

class ABattlefieldActor;
class ULandmarkContainer;
class ACombatant;
class UCombatEvent;
class ABattlefield;

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UBattlefield : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RefreshLandmarksFromWorld();
	
	UFUNCTION(BlueprintPure)
	TArray<ACombatant*> FindCombatantsByTag(FGameplayTag Tag, bool Exact = false) const;
	UFUNCTION(BlueprintPure)
	ACombatant* FindCombatantByTag(FGameplayTag Tag, bool Exact = false) const;
	UFUNCTION(BlueprintPure)
	TArray<ACombatant*> FindCombatantsExceptTag(FGameplayTag Tag, bool Exact = false) const;
	UFUNCTION(BlueprintPure)
	TArray<ACombatant*> FindCombatantsByLocation(const FVector Location, const float Range,
	const bool IncludeZ = false) const;
	UFUNCTION(BlueprintPure)
	TArray<ACombatant*> FindCombatantsByTeamAttitude(const ACombatant* TeamAgent, TEnumAsByte<ETeamAttitude::Type> Attitude) const;
	
	DECLARE_DYNAMIC_DELEGATE_OneParam(FForeachCombatantDelegate, ACombatant*, Combatant);
	UFUNCTION(BlueprintCallable)
	void ForeachCombatants(FForeachCombatantDelegate Predicate) const;
	void ForeachCombatants(TFunctionRef<bool(ACombatant*)> Predicate) const;

	UFUNCTION(BlueprintPure)
	ABattlefieldActor* GetBattlefieldActor() const;

	UFUNCTION(BlueprintPure)
	static UBattlefield* GetBattlefield(const UObject* WorldContextObject);
	
	/**
	 * @brief 地标
	 */
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	ULandmarkContainer* Landmarks;

protected:
	void HandleCombatEvent(const UCombatEvent* CombatEvent);
	void BroadcastCombatEvents();

	UFUNCTION()
	void OnActorSpawned(AActor* InActor);
	UFUNCTION()
	void OnActorDestroyed(AActor* InActor);
	void RegisterCombatant(ACombatant* Combatant);
	void UnregisterCombatant(ACombatant* Combatant);
	
	UPROPERTY(BlueprintReadOnly)
	ABattlefieldActor* BattlefieldActor;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatEventDelegate, const UCombatEvent*, CombatEvent);
	UPROPERTY(BlueprintReadOnly)
	FOnCombatEventDelegate OnCombatEventDelegate;
	
private:
	FDelegateHandle OnActorSpawnedHandle;
	FDelegateHandle OnCombatEventHandle;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly,meta=(AllowPrivateAccess))
	TMap<int32, TSoftObjectPtr<ACombatant>> Combatants;
	
	UPROPERTY(Transient)
	TArray<const UCombatEvent*> QueuedEvents;
	UPROPERTY(VisibleInstanceOnly)
	int32 QueuedEventsMaxCount = 0;
	bool bEventBroadcasting = false;
};


