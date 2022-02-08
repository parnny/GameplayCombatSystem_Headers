// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThreatSituation.h"
#include "ThreatPolicy.generated.h"
class ACombatant;

UCLASS(Abstract,BlueprintType,Blueprintable)
class UThreatPolicy : public UObject
{
	GENERATED_BODY()
public:	
    virtual void ModifyThreat(const ACombatant* Threatened, const ACombatant* Instigator, FThreatSituation& ThreatSituation) const;
	
	UFUNCTION(BlueprintImplementableEvent)
    void BP_ModifyThreat(const ACombatant* Threatened, const ACombatant* Instigator, FThreatSituation InThreatSituation, FThreatSituation& OutThreatSituation) const;
};

UCLASS(BlueprintType,Blueprintable)
class UThreatPolicyPassive : public UThreatPolicy
{
	GENERATED_BODY()
public:
    virtual void ModifyThreat(const ACombatant* Threatened, const ACombatant* Instigator, FThreatSituation& ThreatSituation) const override;
};

UCLASS(BlueprintType,Blueprintable)
class UThreatPolicyTrigger : public UThreatPolicy
{
	GENERATED_BODY()
public:
    virtual void ModifyThreat(const ACombatant* Threatened, const ACombatant* Instigator, FThreatSituation& ThreatSituation) const override;
};