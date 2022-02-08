// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "PerceiveCombatantComponent.generated.h"

UENUM(BlueprintType)
enum class EPerceiveCombatantState : uint8
{
	Found = 0,
	Stay = 1,
	Lose = 2,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCOMBATSYSTEM_API UPerceiveCombatantComponent : public USceneComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams( FPerceiveTicked, UPerceiveCombatantComponent, OnPerceiveTicked, ACombatant*, Combatant, EPerceiveCombatantState, State);

public:	
	// Sets default values for this component's properties
	UPerceiveCombatantComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginDestroy() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float PerceiveRadius = 1000.f;
	
	UPROPERTY(BlueprintReadWrite)
	TSoftObjectPtr<ACombatant> TeamAgent;

	UPROPERTY(BlueprintReadOnly,VisibleInstanceOnly)
	TSet<TSoftObjectPtr<ACombatant>> PerceivedCombatants;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bOnlyXY = true;

	UPROPERTY(BlueprintAssignable)
	FPerceiveTicked OnPerceiveTicked;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCombatantAttitudeFilter AttitudeFilter;
};
