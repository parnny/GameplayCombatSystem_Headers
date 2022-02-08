// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSpellFactory.h"

#include "Spell.h"

UCombatSpellFactory::UCombatSpellFactory()
{
	SupportedClass = USpell::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UCombatSpellFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(USpell::StaticClass()));
	return NewObject<USpell>(InParent,InClass,InName,Flags);
}

bool UCombatSpellFactory::CanCreateNew() const
{
	return true;
}

