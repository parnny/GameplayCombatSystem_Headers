// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Spell/AnimNotify/SpellNotifyState.h"
#include "SpellNotifyState_NavigationMove.generated.h"

class USpellNotifyState_NavigationMove;

UCLASS(BlueprintType)
class USpellNotifyStateInst_NavigationMove : public USpellNotifyStateInst
{
	GENERATED_BODY()
public:
	virtual void NotifySpellBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifySpellTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifySpellEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetTargetActor(AActor* Target);
	
	UPROPERTY(BlueprintReadOnly)
	class USplineComponent* SplineComponent;

	TWeakObjectPtr<AActor> TargetActor;
	
	UPROPERTY(BlueprintReadWrite)
	FFloatRange NavCheckRange;
	
	/**
	 * @brief 移动时间
	 */
	float MoveDuration = 0.f;
	float SplineEndTime = 0.f;
	FVector SpineEndLocation = FVector::ZeroVector;
	FVector LastLocation = FVector::ZeroVector;
	FVector PrimitiveOffset = FVector::ZeroVector;
	bool bFinished = false;
};
/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API USpellNotifyState_NavigationMove : public USpellNotifyState
{
	GENERATED_BODY()
	friend class USpellNotifyStateInst_NavigationMove;
public:
	USpellNotifyState_NavigationMove();

	FString GetNotifyName_Implementation() const override;

protected:
	UPrimitiveComponent* GetCollisionComponent(const AActor* Actor) const;
	bool CollisionSample(const UWorld* World, AActor* Actor,
		FVector StartLocation, FVector EndLocation, FRotator Rotation, AActor* TargetActor) const;
	
	
	FName ComponentName = ACharacter::CapsuleComponentName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUseConstantVelocity = false;
	
	UPROPERTY(BlueprintReadWrite)
	float CollisionSampleTime = 1.f/60.f;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bDrawDebug = false;

	UPROPERTY(EditAnywhere, meta=(EditConditionHides, editcondition = "bDrawDebug"))
	float DrawDuration = 10.f;
#endif
};
