// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatEventInterface.h"
#include "CombatParticle.h"
#include "CombatTeamAgentInterface.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "CombatAvatar.generated.h"

class ACombatant;
USTRUCT()
struct FCombatAvatarMontagePlayed
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly)
	TSoftObjectPtr<UAnimMontage> Montage;
	
	UPROPERTY(VisibleInstanceOnly)
	int32 MontagePriority = -1;
};

class UCombatAvatarAsset;
/**
 * @brief 战斗单元角色
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API ACombatAvatar : public ACharacter, public ICombatTeamAgentInterface, public ICombatEventInterface
{
	GENERATED_UCLASS_BODY()

	// Sets default values for this character's properties
	ACombatAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/**
	 * @brief 表现死亡
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCombatantDead();

	/**
	 * @brief 绑定战斗单元
	 * @param InCombatant 战斗单元
	 */
	void SetCombatant(ACombatant* InCombatant);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCombatantSetup(ACombatant* NewCombatant);
	
	/**
	 * @brief 播放战斗特效
	 * @param Particle 特效配置
	 * @return 特效对象
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    UObject* PlayCombatParticle(FCombatParticle Particle);

	UFUNCTION(BlueprintCallable)
	void PlaySlomoCurve(UCurveFloat* Curve);

	UFUNCTION(BlueprintPure)
	bool ProjectToNavigation(FVector& Location) const;
	
	UFUNCTION(BlueprintCallable)
	FVector SnapToNavigation();

	UFUNCTION(CallInEditor)
	void TestAvatarEntry();

	virtual void HandleCombatEvent(const UCombatEvent* CombatEvent) override;
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="HandleCombatEvent"))
	void BP_HandleCombatEvent(const UCombatEvent* CombatEvent);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACombatAvatar> TestClass;

	UFUNCTION(BlueprintCallable)
	float PlayAvatarMontage(UAnimMontage* MontageToPlay, int32 Priority, float InPlayRate = 1.f, FName StartSection = NAME_None);

	/**
	 * @brief 播放montage
	 * @param Tag 标签
	 * @param Priority
	 * @param InPlayRate
	 * @param StartSection
	 */
	UFUNCTION(BlueprintCallable)
	float PlayTaggedMontage(FGameplayTag Tag, int32 Priority, float InPlayRate = 1.f, FName StartSection = NAME_None);

	UFUNCTION(BlueprintCallable)
	float PlayTaggedAnimAsMontage(FGameplayTag Tag, int32 Priority, FName SlotNodeName = NAME_None, float BlendInTime = 0.25f, float BlendOutTime = 0.25f, float InPlayRate = 1.f, int32 LoopCount = 1, float BlendOutTriggerTime = -1.f, float InTimeToStartMontageAt = 0.f);
	
	UFUNCTION(BlueprintPure)
	int32 GetActiveMontagePriority() const;

	// IGenericTeamAgentInterface
	UFUNCTION(BlueprintCallable)
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	UFUNCTION(BlueprintPure)
	virtual FGenericTeamId GetGenericTeamId() const override;
	
protected:
	/**
	 * @brief 战斗单元
	 */
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	class ACombatant* Combatant;
	/**
	 * @brief 动作配置，支持montage和动作资源
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta=(ForceInlineRow))
	TMap<FGameplayTag,UAnimMontage*> TaggedMontageMap;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta=(ForceInlineRow))
	TMap<FGameplayTag,UAnimSequence*> TaggedAnimMap;

	UPROPERTY(meta=(DeprecationMessage="not used"))
	TMap<FGameplayTag,UAnimSequenceBase*> AvatarAnimMap_DEPRECATED;
	
	UPROPERTY(VisibleInstanceOnly)
	float SlomoTime = 0.f;
	UPROPERTY(VisibleInstanceOnly)
	float SlomoLength = 0.f;
	UPROPERTY(VisibleInstanceOnly)
	UCurveFloat* SlomoCurve;

	UPROPERTY(EditAnywhere)
	FString ActiveBehaviorTreeNode;
	
private:
	UPROPERTY(Category=Avatar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleInstanceOnly)
	FCombatAvatarMontagePlayed MontagePlayed;
};