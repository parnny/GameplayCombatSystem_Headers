// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "BattlefieldLandmark.generated.h"

UCLASS(Blueprintable,BlueprintType)
class ULandmarkContainer : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure)
	FVector GetLandmark(FName Name, bool bIncludeParent=true) const;
	
	UFUNCTION(BlueprintPure)
	bool HasLandmark(FName Name, bool bIncludeParent=true) const;

	UFUNCTION(BlueprintCallable)
	void SetLandmarkLocation(FName Name, FVector Location);
	
	UFUNCTION(BlueprintCallable)
	void SetLandmarkActor(FName Name, AActor* Actor);
	
	UFUNCTION(BlueprintCallable)
	void RemoveLandmark(FName Name);
	UFUNCTION(BlueprintCallable)
	void RemoveLandmarkLocation(FName Name);
	UFUNCTION(BlueprintCallable)
	void RemoveLandmarkActor(FName Name);

	UFUNCTION(BlueprintCallable)
	void ClearLandmark();
	UFUNCTION(BlueprintCallable)
	void ClearLandmarkLocation();
	UFUNCTION(BlueprintCallable)
	void ClearLandmarkActor();

	UFUNCTION(BlueprintCallable)
	void SetParentContainer(ULandmarkContainer* Parent);

protected:
	UPROPERTY(VisibleInstanceOnly)
	TMap<FName,FVector> LandmarkLocation;
	
	UPROPERTY(VisibleInstanceOnly)
	TMap<FName,TSoftObjectPtr<AActor>> LandmarkActor;
	
	UPROPERTY()
	TSoftObjectPtr<ULandmarkContainer> ParentContainer;
};
