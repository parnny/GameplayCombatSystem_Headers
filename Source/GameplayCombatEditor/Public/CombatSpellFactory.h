// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CombatSpellFactory.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATEDITOR_API UCombatSpellFactory : public UFactory
{
	GENERATED_BODY()
public:
	UCombatSpellFactory();

	// UFactory Interface Begin
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
	// UFactory Interface End
};
