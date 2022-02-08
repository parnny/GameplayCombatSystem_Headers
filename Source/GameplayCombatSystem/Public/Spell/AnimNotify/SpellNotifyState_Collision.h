// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/AnimNotify/SpellNotifyState.h"
#include "SpellNotifyState_Collision.generated.h"

/**
* @brief 异步任务的事件定义
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpellNotifyStateCollisionSingle, FGameplayTag, EventTag, FHitResult, SweepResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellNotifyStateCollisionMulti, FGameplayTag, EventTag,const TArray<FHitResult>&, SweepResults, FVector, TraceStart, FVector, TraceEnd);

class USphereComponent;

UCLASS(BlueprintType,Blueprintable,Abstract)
class USpellNotifyState_CollisionHandler : public UObject
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	bool FilterResult(USpell* Spell, FGameplayTag EventTag, FHitResult SweepResult, FVector TraceStart, FVector TraceEnd);

	UFUNCTION(BlueprintImplementableEvent)
	bool HandleResult(USpell* Spell, FGameplayTag EventTag, FHitResult SweepResult, FVector TraceStart, FVector TraceEnd);
};

UCLASS(BlueprintType)
class USpellNotifyStateInst_Collision : public USpellNotifyStateInst
{
	GENERATED_BODY()
public:
	virtual void NotifySpellBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifySpellTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifySpellEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UFUNCTION(BlueprintCallable)
	void SetCollisionHandler(USpellNotifyState_CollisionHandler* Handler);

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	TSoftObjectPtr<USpellNotifyState_CollisionHandler> CollisionHandler;

	UPROPERTY(BlueprintAssignable)
	FSpellNotifyStateCollisionSingle OnCollisionOverlap;

	UPROPERTY(BlueprintAssignable)
	FSpellNotifyStateCollisionMulti OnComponentSweepMulti;

protected:	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPrimitiveComponent* GetCollisionComponent(const USkeletalMeshComponent* MeshComp) const;
	
	FVector LastLocation = FVector::ZeroVector;

private:
	void DebugArea(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API USpellNotifyState_Collision : public USpellNotifyState
{
	GENERATED_BODY()
public:
	USpellNotifyState_Collision();
	
	FString GetNotifyName_Implementation() const override;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bDrawDebug = false;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bDrawDebug"))
	bool bDrawDebugImpactPoint = false;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bDrawDebug"))
	bool bDrawDebugImpactNormal = false;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bDrawDebug"))
	bool bDrawDebugTraceDelta = false;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bDrawDebug"))
	bool bDrawDebugTraceShape = false;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bDrawDebug"))
	bool bDrawDebugBone = false;
#endif
	
	// 指定某武器的某碰撞盒
	UPROPERTY(EditAnywhere, meta=(AnimNotifyBoneName = "true"))
	FName SocketName = "WeaponPoint_L";
	UPROPERTY(EditAnywhere)
	FName ComponentName = NAME_None;
};
