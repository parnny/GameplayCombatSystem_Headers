// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UAnimNotify_SpawnActor : public UAnimNotify
{
	GENERATED_UCLASS_BODY()
public:	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	virtual FString GetNotifyName_Implementation() const override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere)
	bool bAttachToSocket = false;
	
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "!bAttachToSocket"))
	bool bUsingSocketTransform = false;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bAttachToSocket"),Category="AttachToSocket")
	EAttachmentRule LocationRule;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bAttachToSocket"),Category="AttachToSocket")
	EAttachmentRule RotationRule;
	UPROPERTY(EditAnywhere,meta=(EditConditionHides, editcondition = "bAttachToSocket"),Category="AttachToSocket")
	EAttachmentRule ScaleRule;

	UPROPERTY(EditAnywhere, meta=(AnimNotifyBoneName = "true",EditConditionHides, editcondition = "bAttachToSocket || bUsingSocketTransform"))
	FName SocketName = NAME_None;

	UPROPERTY(EditAnywhere)
	FVector LocationOffset;

	UPROPERTY(EditAnywhere)
	FRotator RotatorOffset;
};
