// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "CombatantComponent.h"
#include "SpellDefine.h"
#include "SpellComponent.generated.h"


class USpell;
/**
 * @brief 技能组件
 * 管理战斗单位技能实例
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCOMBATSYSTEM_API USpellComponent : public UActorComponent, public ICombatEventInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellComponent();
	virtual void BeginDestroy() override;

	// Called every frame
	/**
	 * @brief 即时战斗技能CD的拓展入口
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// >>>>>>>> ICombatEventInterface
	virtual void HandleCombatEvent(const class UCombatEvent* CombatEvent) override;
	/**
	 * @brief 获取技能map
	 * @return 技能map
	 */
	UFUNCTION(BlueprintPure)
	TMap<FName, USpell*> GetSpellMap() const;
	/**
	 * @brief 学习技能
	 * @param SpellID 学习名称
	 * @param SpellClass 技能类
	 */
	UFUNCTION(BlueprintCallable)
	USpell* LearnSpell(FName SpellID, TSubclassOf<USpell> SpellClass);
	/**
	 * @brief 遗忘技能
	 * @param SpellID 技能名称
	 */
	UFUNCTION(BlueprintCallable)
	void ForgetSpell(FName SpellID);
	/**
	 * @brief 释放技能
	 * @param SpellID 技能名称
	 * @param CastParam 技能参数
	 * @param Errors 
	 * @return 释放结果
	 */
	UFUNCTION(BlueprintCallable)
	bool CastSpell(FName SpellID, const FSpellCastParameter CastParam, FGameplayTagContainer& Errors);
	/**
	 * @brief 遗忘所有技能
	 */
	UFUNCTION(BlueprintCallable)
	void ForgetAllSpells();
	/**
	 * @brief 通过技能类获取技能（同一个技能类可能存在多个实例）
	 * @param SpellClass 技能类
	 * @return 技能实例
	 */
	UFUNCTION(BlueprintPure)
	USpell* FindSpell(TSubclassOf<USpell> SpellClass) const;
	/**
	 * @brief 通过技能名称获取技能
	 * @param SpellID 技能名称
	 * @return 技能实例
	 */
	UFUNCTION(BlueprintPure)
	USpell* FindSpellByID(FName SpellID);

	UFUNCTION(BlueprintPure)
	USpell* FindSpellByTag(FGameplayTag SpellTag, bool Exact);

	UFUNCTION(BlueprintPure)
	TArray<TSoftObjectPtr<USpell>> FindSpellsByTag(FGameplayTag SpellTag, bool Exact);

	UFUNCTION(BlueprintPure)
	bool HasAnySpellCasting() const;

	UFUNCTION(BlueprintPure)
	USpell* GetAnyCastingSpell() const;

protected:
	/**
	 * @brief 存储技能实例的容器
	 */
	UPROPERTY(VisibleInstanceOnly)
	TMap<FName, USpell*> SpellMap;
};
