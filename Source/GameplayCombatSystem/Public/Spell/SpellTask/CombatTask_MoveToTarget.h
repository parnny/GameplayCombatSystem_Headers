#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "CombatTask_MoveToTarget.generated.h"

class USpell;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpellTaskMoveToTarget);

/**
 * 
 */
UCLASS()
class GAMEPLAYCOMBATSYSTEM_API UCombatTask_MoveToTarget : public UGameplayTask
{
	GENERATED_BODY()

public:
	UCombatTask_MoveToTarget(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, meta = (HidePin = "Spell", DefaultToSelf = "Spell", BlueprintInternalUseOnly = "TRUE"))
	static UCombatTask_MoveToTarget* SpellMoveToTarget(USpell* Spell, FVector TargetLocation, UCurveFloat* MoveCurve, AActor* Avatar=nullptr, bool LookAtTarget=true);

	virtual void TickTask(float DeltaTime) override;

protected:
	virtual void Activate() override;

	UPROPERTY()
	USpell* Spell;

	UPROPERTY()
	AActor* Avatar;

	UPROPERTY()
	UCurveFloat* MoveCurve;

	FVector SourceLocation;
	FVector TargetLocation;

	float Duration;

	bool LookAtTarget = true;

    UPROPERTY(BlueprintAssignable)
	FSpellTaskMoveToTarget MoveFinished;
};
