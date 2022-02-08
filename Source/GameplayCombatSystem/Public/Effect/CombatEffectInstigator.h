// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatEffectInstigator.generated.h"

class UCombatTargetType;
struct FCombatEffectContainerSpec;
struct FGameplayTag;
class ACombatant;
class ICombatVariableInterface;
class UCombatEffect;

// This class does not need to be modified.
UINTERFACE(BlueprintType,meta = (CannotImplementInterfaceInBlueprint))
class UCombatEffectInstigator : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief 管理效果实例的接口
 */
class GAMEPLAYCOMBATSYSTEM_API ICombatEffectInstigator
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	/**
	 * @brief 获取展示名称
	 * @return 名称
	 */
	virtual FName GetDisplayName() = 0;
	/**
	 * @brief 获取创建效果的战斗单位
	 * @return 创建效果的战斗单位
	 */
	virtual ACombatant* GetOwnerCombatant() = 0;
	void OnCombatEffectCreated(UCombatEffect* CombatEffect);

	UCombatEffect* CreateCombatEffect(const FName Key, TSubclassOf<UCombatEffect> EffectClass);
	UCombatEffect* FindCombatEffect(const FName Key);
	
	UCombatTargetType* GetOrCreateTargetBuilder(const FName Key, const TSubclassOf<UCombatTargetType> BuilderClass);
	
	bool SyncStructureToOther(const FName SyncFrom_PropName, UObject* SyncTo_Object, const FName SyncTo_PropName = "Config");
	
	virtual void DestroyCombatEffects();
	virtual void DestroyCombatTargetBuilders();

	// 战斗效果的应用接口
	void OnCombatEffectApplied(UCombatEffect* CombatEffect,ACombatant* Target, UObject* ApplySpec);

	UFUNCTION(BlueprintCallable)
	virtual void ApplyCombatEffect(const FName Key, TSoftObjectPtr<ACombatant> Target, UObject* ApplySpec);

	virtual FGameplayTagContainer& GetEffectParentTags() = 0;
	
protected:
	virtual FCombatEffectContainerSpec* FindEffectContainerSpec(const FName Key) = 0;
	virtual TMap<FName, UCombatEffect*>& GetEffectContainer() = 0;
	virtual TMap<FName, UCombatTargetType*>& GetTargetBuilderContainer() = 0;
};
