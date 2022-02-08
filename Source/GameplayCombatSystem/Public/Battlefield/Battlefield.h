// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Combatant/Combatant.h"
#include "Battlefield.generated.h"

UCLASS()
class GAMEPLAYCOMBATSYSTEM_API ABattlefield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattlefield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	ACombatant* CreateCombatant(FName CombatantName, TSubclassOf<ACombatant> CombatantClass);


	TMap<FName, ACombatant*> Combatants;

};
