// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatCreatureInterface.generated.h"

class ICombatEffectInstigator;
class ACombatant;
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCombatCreatureInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API ICombatCreatureInterface
{
	GENERATED_IINTERFACE_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool PostInitialize(ACombatant* Creator,const TScriptInterface<ICombatEffectInstigator>& EffectInstigator);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnCreatorDestroyed(ACombatant* Creator);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInstigatorDestroyed(const TScriptInterface<ICombatEffectInstigator>& EffectInstigator);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GetNavigationQueryExtent(FVector& QueryExtent);
};
