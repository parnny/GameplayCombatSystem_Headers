// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "SplineMovementComponent.generated.h"

class UCurveVector;

USTRUCT(BlueprintType)
struct FSplineControlPoint
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplinePoint)
	float InputKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplinePoint)
	FBox Offset;

	FVector GetRandomPoint() const
	{
		return FMath::RandPointInBox(Offset);
	}
};

/**
 * 
 */
UCLASS(ClassGroup=Movement, meta=(BlueprintSpawnableComponent),HideCategories=Velocity)
class GAMEPLAYCOMBATSYSTEM_API USplineMovementComponent : public UMovementComponent
{
	GENERATED_UCLASS_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSplineStopDelegate);
	
	//Begin UActorComponent Interface
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;
	//End UActorComponent Interface

	//Begin UMovementComponent Interface
	virtual void StopMovementImmediately() override;
	//End UMovementComponent Interface
	
	UFUNCTION(BlueprintCallable, Category = "Control")
	void FinaliseControlPoints();
	
	/* Reset to start. Sets time to zero and direction to 1.  */
	UFUNCTION(BlueprintCallable, Category = "Control")
	void RestartMovement();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSplineControlPoint> ControlPoints;
	
	UPROPERTY(VisibleInstanceOnly)
	UCurveVector* CurveVector;

	UPROPERTY(BlueprintReadWrite)
	TSoftObjectPtr<USceneComponent> TargetComponent;
	
	UPROPERTY(BlueprintReadWrite)
	FName TargetSocket;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta=(ToolTip="If True, Stop Movement When Loss Target Actor"))
	bool bTargetRequired = true;
	
	UPROPERTY(BlueprintReadWrite,VisibleInstanceOnly)
	FVector StartLocation;
	
	UPROPERTY(BlueprintReadOnly,VisibleInstanceOnly)
	FVector TargetLocation;
	
	UPROPERTY(BlueprintReadOnly,VisibleInstanceOnly)
	float TimeGone;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration;

	void SplineMoveStop();

protected:
	UPROPERTY(BlueprintAssignable)
	FOnSplineStopDelegate OnSplineStopDelegate;
	
	/** If true, will sweep for blocking collision during movement. If false, it will simply teleport to the next position and ignore collision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	bool bSweep = true;

	/** Physics teleport type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	ETeleportType TeleportType = ETeleportType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFollowTarget = true;
	
private:
	bool bStopped = false;
};
