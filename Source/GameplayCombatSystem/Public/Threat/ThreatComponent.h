// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "CombatantComponent.h"
#include "ThreatSituation.h"
#include "ThreatComponent.generated.h"

class UThreatPolicy;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FThreatListUpdate,UThreatComponent,OnThreatListUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCOMBATSYSTEM_API UThreatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThreatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TickThreat();

	UFUNCTION(BlueprintCallable)
	void BeStimulused(const ACombatant* Instigator, bool BeStimulus);

	UFUNCTION(BlueprintCallable)
	void BeThreatened(const ACombatant* Instigator, float ThreatValue);

	UFUNCTION(BlueprintCallable)
	bool IncreaseThreat(const ACombatant* Instigator, float ThreatValue);
	
	UFUNCTION(BlueprintCallable)
	void RemoveThreat(const ACombatant* Instigator);
	
	UFUNCTION(BlueprintCallable)
	void ClearThreat(const ACombatant* Instigator);

	UFUNCTION(BlueprintPure)
	void QueryThreatSituation(const ACombatant* Instigator, FThreatSituation& ThreatSituation) const;

	UFUNCTION(BlueprintCallable)
	void ReSetThreatSituation(const ACombatant* Instigator, FThreatSituation ThreatSituation);

	UFUNCTION(BlueprintPure)
	TArray<TSoftObjectPtr<ACombatant>> GetThreatInstigators() const;

	UFUNCTION(BlueprintPure)
	bool HasThreatSituation() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void ClearThreatSituations();

	void BroadcastStimulusEvent(const ACombatant* Instigator, bool BeStimulus);
	void BroadcastThreatEvent();

	UFUNCTION(BlueprintCallable)
	static bool ModifyThreat(FThreatSituation InThreatSituation, float ModifyValue, EThreadModifyReason Reason, FThreatSituation& OutThreatSituation, int ModifyCD=0);

	UFUNCTION(BlueprintPure)
	TSoftObjectPtr<ACombatant> QueryHightThreat(TSoftObjectPtr<ACombatant> PriorInstigator) const;


protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TMap<TSoftObjectPtr<ACombatant>, FThreatSituation> ThreatSituations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bHasGeneratePolicy = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bHasUpdatePolicy = false;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta=(editcondition = "bHasGeneratePolicy", MultiLine="true"))
	TSubclassOf<UThreatPolicy> GeneratePolicy;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta=(editcondition = "bHasUpdatePolicy", MultiLine="true"))
	TSubclassOf<UThreatPolicy> TickPolicy;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta=(editcondition = "bHasUpdatePolicy", MultiLine="true"))
	TSubclassOf<UThreatPolicy> UpdatePolicy;
	
	int32 ListChangeCount = 0;
	bool bIsThreatListChanged = false;
public:
	UPROPERTY(BlueprintAssignable)
	FThreatListUpdate OnThreatListUpdate;
};
