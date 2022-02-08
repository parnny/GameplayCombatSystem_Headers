// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTasksComponent.h"
#include "CombatantComponent.generated.h"

class UCombatStatusComponent;
class ABattlefield;
class USpellComponent;
class UAuraComponent;
class UAttributeStatsComponent;
class UThreatComponent;
class UCombatTaskComponent;

/**
 * @brief 战斗单元组件基类
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), HideCategories=(Tags,Cooking,Activation,AssetUserData,Collision))
class GAMEPLAYCOMBATSYSTEM_API UCombatantComponent : public UGameplayTasksComponent
{
	GENERATED_UCLASS_BODY()
	
	virtual void BeginPlay() override;
protected:
	virtual void OnRegister() override;
	
private:	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USpellComponent* SpellComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UAuraComponent* AuraComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UAttributeStatsComponent* AttributeComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UThreatComponent* ThreatComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UCombatStatusComponent* StatusComponent;
	
	UPROPERTY(VisibleInstanceOnly)
	TSet<AActor*> SpawnedCreatures;
};
