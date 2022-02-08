// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatAbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCOMBATSYSTEM_API UCombatAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void LearnAbility(TSubclassOf<class UCombatAbility> AbilityClass);
	void ForgetAbility(TSubclassOf<class UCombatAbility> AbilityClass);
	void HandleCombatEffect(class UCombatEffect* CombatEffect);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSet<TSubclassOf<class UCombatAbility>> AbilityClasses;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TMap<FName,class UCombatAbility*> AbilityMap;
};
