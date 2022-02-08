// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatParticle.generated.h"

class UParticleSystemComponent;
class UNiagaraComponent;
class ACombatAvatar;
class ACombatParticleActor;

UENUM(BlueprintType)
enum class ECombatParticleLocationRule: uint8
{
	WorldLocation UMETA(DisplayName = "世界位置"),
	AttachToSocket UMETA(DisplayName = "绑定到骨骼"),
	SocketLocation UMETA(DisplayName = "使用骨骼位置(不绑定)"),
};

/**
 * @brief 战斗特效的配置类，仅支持 ParticleSystem, NiagaraSystem
 *	具体字段参考具体特效系统的解释
 */
USTRUCT(BlueprintType)
struct FCombatParticle
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,meta=(AllowedClasses="ParticleSystem, NiagaraSystem", ExactClass=true))
	UObject* Asset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ECombatParticleLocationRule SpawnRule;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(EditConditionHides, editcondition = "SpawnRule != ECombatParticleLocationRule::WorldLocation"))
	FName AttachPointName = NAME_None;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(EditConditionHides, editcondition = "SpawnRule != ECombatParticleLocationRule::WorldLocation"))
	FVector Location = FVector::ZeroVector;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(EditConditionHides, editcondition = "SpawnRule != ECombatParticleLocationRule::WorldLocation"))
	FRotator Rotation = FRotator::ZeroRotator;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(EditConditionHides, editcondition = "SpawnRule != ECombatParticleLocationRule::WorldLocation"))
	FVector Scale = FVector(1.f);
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,meta=(EditConditionHides, editcondition = "SpawnRule == ECombatParticleLocationRule::AttachToSocket"))
	TEnumAsByte<EAttachLocation::Type> LocationType = EAttachLocation::KeepRelativeOffset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bAutoDestroy = true;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EPSCPoolMethod PoolingMethod = EPSCPoolMethod::None;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bAutoActivate=true;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bPreCullCheck = true;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 TranslucentSortPriority = 0;
};

/**
 * @brief 为蓝图特效提供基类，目前没有特别的使用必要，如果有必要在Actor中限定特效Actor，可以继承此类
 */
UCLASS(BlueprintType,Blueprintable)
class ACombatParticleActor : public AActor
{
	GENERATED_BODY()
};


UCLASS()
class UCombatParticleFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UFXSystemComponent* SpawnCombatParticle(ACombatAvatar* Avatar, FCombatParticle ParticleConfig);
};