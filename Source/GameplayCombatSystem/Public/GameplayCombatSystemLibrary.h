// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AttributeBase.h"
#include "Combatant.h"
#include "CombatGlobalDefine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Perception/AIPerceptionTypes.h"
#include "GameplayCombatSystemLibrary.generated.h"

class UAISense;
class UAISenseConfig;
class UAISenseConfig_Sight;
class USpell;
/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

USTRUCT()
struct FCombatantTargetScore
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly)
	TSoftObjectPtr<ACombatant> Target;
	
	UPROPERTY(VisibleInstanceOnly,Category="Distance")
	float Distance;
	UPROPERTY(VisibleInstanceOnly,Category="Distance")
	float Distance_Score = 0;

	UPROPERTY(VisibleInstanceOnly,Category="Axis")
	float Axis_Angle;
	UPROPERTY(VisibleInstanceOnly,Category="Axis")
	float Axis_Score = 0;
	
	UPROPERTY(VisibleInstanceOnly,Category="Camera")
	float Camera_Angle;
	UPROPERTY(VisibleInstanceOnly,Category="Camera")
	float Camera_Score = 0;
};


USTRUCT(BlueprintType)
struct FAISenseConfig_SetSight
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0))
	float SightRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0))
		float LoseSightRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sense", config, meta=(UIMin = 0.0, ClampMin = 0.0, UIMax = 180.0, ClampMax = 180.0, DisplayName="PeripheralVisionHalfAngleDegrees"))
		float PeripheralVisionAngleDegrees;

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sense", config)
		FAISenseAffiliationFilter DetectionByAffiliation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sense", config)
		float AutoSuccessRangeFromLastSeenLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0))
		float PointOfViewBackwardOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0))
		float NearClippingRadius;

	void SetConfig(UAISenseConfig_Sight* Config);
};

UCLASS()
class UGameplayCombatSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure)
	static FRotator FindLookAtRotationMaskZ(const FVector& Src, const FVector& Des);

	UFUNCTION(BlueprintPure)
	static ACombatant* CombatantAutoTarget(ACombatant* Combatant,FVector Axis, FFloatRange SpellRange);

	UFUNCTION(BlueprintPure)
	static FVector GetAxisValue(ACombatant* Combatant, FName X = NAME_None, FName Y = NAME_None, FName Z = NAME_None);

	UFUNCTION(BlueprintPure)
	static ETeamAttitude::Type GetTeamAttitudeTowards(const AActor* A, const AActor* B);

	UFUNCTION(BlueprintCallable)
	static void SetSightSenseConfig(UAIPerceptionComponent* Perception, FAISenseConfig_SetSight SightConfig);

	UFUNCTION(BlueprintCallable)
	static void CallLevelBlueprint(const UObject* WorldContextObject, FName FunctionName);

	UFUNCTION(BlueprintCallable)
	static void PrintChildGameplayTags(FGameplayTag ParentTag);

	UFUNCTION(BlueprintPure)
	static bool SimulateSweep(UPrimitiveComponent* Primitive, FVector Location, FRotator Rotation,TArray<FHitResult>& SweepResults);

	UFUNCTION(BlueprintCallable)
	static float SetTimeDilation(const UObject* WorldContextObject, float NewTimeDilation, ETimeDilationType DialtionType);
	
	UFUNCTION(BlueprintCallable)
	static void CancelTimeDilation(const UObject* WorldContextObject, ETimeDilationType DialtionType);
};
