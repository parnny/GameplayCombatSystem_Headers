// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Combatant.h"
#include "CombatEffectInstigator.h"
#include "CombatWorldObject.h"
#include "Kismet/KismetSystemLibrary.h"

#include "CombatEffect.generated.h"

/**
 * @brief 战斗效果与配置的关联
 *	在触发战斗效果实例时，读取技能/光环蓝图中，对应的配置结构体，以反射的形式，将参数拷贝到技能实例中
 *	为效果实例提供配置数据
 */
USTRUCT(BlueprintType)
struct FCombatEffectSpec
{
	GENERATED_USTRUCT_BODY()
	/**
	 * @brief 效果类
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UCombatEffect> EffectClass;
	/**
	 * @brief 改效果对应的配置变量
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName ConfigName;
};

/**
 * @brief 效果容器，对使用{TargetType}筛选的战斗单位，附件{CombatEffectSpecs}配置的效果
 */
USTRUCT(BlueprintType)
struct FCombatEffectContainer
{
	GENERATED_USTRUCT_BODY()
	/**
     * @brief 构建目标的类，此处虽然配置的是类，实际使用的为该类的CDO
     */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UCombatTargetType> TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bUsingTargetConfig = false;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, meta=(editcondition = "bUsingTargetConfig"))
	FName TargetConfig;
	
	/**
	 * @brief 效果列表的配置
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(ForceInlineRow))
	TArray<FCombatEffectSpec> CombatEffectSpecs;

	/**
	 * @brief 构建目标列表
	 * @param EffectOwner 效果创建者
	 * @param Instigator 效果的来源
	 * @param RawTarget 效果目标
	 */
	TArray<ACombatant*> RebuildTargets(ACombatant* EffectOwner, TScriptInterface<ICombatEffectInstigator> Instigator, TSoftObjectPtr<ACombatant> RawTarget);
};

/**
 * @brief 管理效果容器
 */
USTRUCT(BlueprintType)
struct FCombatEffectContainerSpec
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief 管理效果容器
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(ForceInlineRow))
	TArray<FCombatEffectContainer> CombatEffectContainers;

	/**
	 * @brief 创建效果实例
	 * @param Instigator 效果实例的来源
	 * @param EffectOwner
	 */
	void CreateCombatEffects(TScriptInterface<ICombatEffectInstigator> Instigator, const ACombatant* EffectOwner=nullptr);
	/**
	 * @brief 应用效果实例
	 * @param Instigator 效果实例的来源
	 * @param ApplyTarget 效果应用的目标
	 * @param ApplySpec
	 */
	void ApplyCombatEffect(UObject* Instigator, TSoftObjectPtr<ACombatant> ApplyTarget, UObject* ApplySpec);

	bool bIsEffectsCreated = false;
};

/**
 * @brief 战斗效果
 *	需要再蓝图中继承，实现具体效果
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UCombatEffect
	: public UCombatWorldObject
	, public ICombatTagInterface
{
	GENERATED_BODY()

	friend struct FCombatEffectSpec;
	friend struct FCombatEffectContainerSpec;
public:
	/**
	 * @brief 创建效果
	 */
	UFUNCTION(BlueprintCallable)
	void OnCombatEffectCreated();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCombatEffectCreated"), Category="Override")
    void BP_OnCombatEffectCreated();
	/**
	 * @brief 效果销毁
	 */
	UFUNCTION(BlueprintCallable)
	void OnCombatEffectDestroy();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCombatEffectDestroy"), Category="Override")
    void BP_OnCombatEffectDestroy();
	/**
	 * @brief 应用效果
	 * @param DesCombatant 效果的应用目标
	 * @return 应用成功
	 */
	UFUNCTION(BlueprintCallable)
	bool ApplyCombatEffect(ACombatant* DesCombatant, UObject* ApplySpec);
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="ApplyCombatEffect"), Category="Override")
    bool BP_ApplyCombatEffect(ACombatant* DesCombatant, UObject* ApplySpec);
	/**
	 * @brief 展示战斗效果
	 * @param DesCombatant 效果展示的目标
	 */
	UFUNCTION(BlueprintCallable)
	bool PlayCombatEffect(ACombatant* DesCombatant, UObject* ApplySpec);
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="PlayCombatEffect"), Category="Override")
    bool BP_PlayCombatEffect(ACombatant* DesCombatant, UObject* ApplySpec);

	void InitEffect(const ACombatant* Owner, const TScriptInterface<ICombatEffectInstigator> InInstigator);

	UFUNCTION(BlueprintPure)
		virtual FGameplayTagContainer& GetGameplayTagContainer() override;
	virtual void AddGameplayTag(const FGameplayTag& Tag) override;
	UFUNCTION(BlueprintCallable)
		virtual void AddGameplayTag(const FName TagName) override;
	virtual void RemoveGameplayTag(const FGameplayTag& Tag, bool bDeferParentTags) override;
	UFUNCTION(BlueprintCallable)
		virtual void RemoveGameplayTag(const FName TagName, bool bDeferParentTags) override;
	virtual bool HasGameplayTag(const FGameplayTag& Tag, bool Exact) const override;
	UFUNCTION()
		virtual bool HasGameplayTag(const FName TagName, bool Exact) const override;
	UFUNCTION(BlueprintPure, meta = (DisplayName = "HasGameplayTag"))
		virtual bool BP_HasGameplayTag(const FGameplayTag Tag, bool Exact) const override;
	virtual void PostGameplayTagChanged(const FGameplayTag Tag, bool bRemove) override;


	UFUNCTION(BlueprintCallable)
	AActor* SpawnSubActor(TSubclassOf<AActor> Class, FTransform Transform);
	/**
	 * @brief 创建效果的战斗单位
	 */
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ACombatant> EffectOwner;
	/**
	* @brief 创建效果的元素
	*/
	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<ICombatEffectInstigator> Instigator;
	/**
	 * @brief 效果的标签
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer EffectTags;

protected:
	bool SyncConfigFromInstigator(const FName SyncFrom, const FName SyncTo = "Config");	

	UPROPERTY(EditDefaultsOnly,meta=(MustImplement = CombatEffectPlayer), Category="EffectPlayer")
	TSubclassOf<AActor> EffectPlayerClass;

	UPROPERTY(VisibleInstanceOnly, Category="EffectPlayer")
	AActor* EffectPlayerActor;
};
