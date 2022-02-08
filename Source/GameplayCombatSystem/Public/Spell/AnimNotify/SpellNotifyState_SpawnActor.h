// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/AnimNotify/SpellNotifyState.h"
#include "SpellNotifyState_SpawnActor.generated.h"

UCLASS(BlueprintType)
class USpellNotifyStateInst_SpawnActor : public USpellNotifyStateInst
{
	GENERATED_BODY()
public:
	virtual void NotifySpellBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifySpellEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
private:
	UPROPERTY()
	TWeakObjectPtr<AActor> SpawnedActor;
};

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API USpellNotifyState_SpawnActor : public USpellNotifyState
{
	GENERATED_UCLASS_BODY()

	virtual FString GetNotifyName_Implementation() const override;

	AActor* SpawnActor(USkeletalMeshComponent* MeshComp) const;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere)
	bool bAttachToSocket = false;
	
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "!bAttachToSocket"))
	bool bUsingSocketTransform = false;

	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bAttachToSocket"),Category="AttachToSocket")
	EAttachmentRule LocationRule = EAttachmentRule::SnapToTarget;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bAttachToSocket"),Category="AttachToSocket")
	EAttachmentRule RotationRule = EAttachmentRule::SnapToTarget;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bAttachToSocket"),Category="AttachToSocket")
	EAttachmentRule ScaleRule = EAttachmentRule::SnapToTarget;

	UPROPERTY(EditAnywhere, meta=(AnimNotifyBoneName = "true",EditConditionHides, editcondition = "bAttachToSocket || bUsingSocketTransform"))
	FName SocketName = NAME_None;

	UPROPERTY(EditAnywhere)
	FVector LocationOffset;

	UPROPERTY(EditAnywhere)
	FRotator RotatorOffset;

	UPROPERTY(EditAnywhere)
	bool bAutoDestroy = true;
};
