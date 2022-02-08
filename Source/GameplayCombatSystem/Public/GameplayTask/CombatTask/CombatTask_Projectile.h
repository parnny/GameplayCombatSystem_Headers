// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "CombatTask_Projectile.generated.h"

USTRUCT(BlueprintType)
struct FProjectileConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTransform SpawnTransform;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector TargetLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bConstantTime;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Velocity = 100.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TotalTime = 1;
};

USTRUCT()
struct FProjectileSpec
{
	GENERATED_BODY()

	UPROPERTY()
	FProjectileConfig Config;
	
	UPROPERTY()
	AActor* Projectile;
	
	FVector SrcLocation;

	UPROPERTY()
	UPrimitiveComponent* OverlappedComponent;
};

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatTask_Projectile : public UGameplayTask
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTaskProjectileDelegate, AActor*, Projectile, FHitResult, HitResult);
	
	virtual void Activate() override;
	
	UPROPERTY(BlueprintAssignable)
	FTaskProjectileDelegate OnCompleted;
	UPROPERTY(BlueprintAssignable)
	FTaskProjectileDelegate OnOverlapped;

	/** Wait specified time. This is functionally the same as a standard Delay node. */
	UFUNCTION(BlueprintCallable, Category = "CombatTasks", meta = (DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "TRUE"))
	static UCombatTask_Projectile* TaskProjectile(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner,TArray<FProjectileConfig> ProjectileConfigs);

	virtual void TickTask(float DeltaTime) override;

protected:
	virtual void OnDestroy(bool bInOwnerFinished) override;

	bool TickProjectile(const FProjectileSpec& ProjectileSpec, float DeltaTime) const;
	void DestroyProjectile(FProjectileSpec& ProjectileSpec);

	void PostProjectileSpawned(FProjectileSpec& ProjectileSpec);

	UFUNCTION()
	void OnProjectileOverlapped(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& OverlapInfo);

	TArray<FProjectileConfig> ProjectileConfigs;

	TArray<FProjectileSpec> Projectiles;

	FVector SrcLocation;

	float Ticked;
};
