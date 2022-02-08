// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Combatant.h"
#include "UObject/NoExportTypes.h"
#include "SpellDefine.generated.h"

class USpellNotifyState;
class USpellCustomCost;
class USpell;


USTRUCT(BlueprintType)
struct FSpellTargetAttitude : public FCombatantAttitudeFilter
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FSpellCastParameter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSoftObjectPtr<ACombatant> Target;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ConsumeScale = 1.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector Origin = FVector::ZeroVector;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector Direction = FVector::ZeroVector;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float Range = 0;
};

USTRUCT(BlueprintType)
struct FSpellEventData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	ACombatant* Instigator;
};

USTRUCT(BlueprintType)
struct FSpellCooldown
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(ForceUnits=s))
	float Duration = 1.f;
	
	UPROPERTY(BlueprintReadWrite,VisibleInstanceOnly,meta=(ForceUnits=s))
	float TimeGone = 0.f;

	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	bool IsCooldown = false;

	void SetCooldown();
	
	bool Tick(float DeltaTime);
};

USTRUCT(BlueprintType)
struct FSpellCharge
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,VisibleInstanceOnly)
	int32 Value = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHasMaxCharge = false;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, meta=(editcondition="bHasMaxCharge"))
	int32 MaxValue = 1;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	bool bAutoCharge = true;
	
	void Charge(int32 ChargeValue);
	void SetCharge(int32 NewValue);
	void Cost(int32 SubValue=1);
	bool IsMaxCharge() const;
	bool IsCharging() const;
};

/**
* @brief 技能消耗配置
*/
USTRUCT(BlueprintType,meta=(InlineCategoryProperty))
struct FSpellCost
{ 
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bCostEnergy = false;
	/**
	* @brief 消耗能量
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(editcondition = "bCostEnergy", MultiLine="true",ForceInlineRow))
	TMap<FGameplayTag, float> CostEnergies;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bCostCharge = false;
	/**
	* @brief 消耗充能
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(editcondition = "bCostCharge", MultiLine="true"))
	int32 CostCharge = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, InlineEditConditionToggle))
	bool bUseCustomCost = false;
	/**
	* @brief 自定义消耗
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(editcondition = "bUseCustomCost", MultiLine="true"))
	TSubclassOf<USpellCustomCost> CustomCostClass;
};

USTRUCT(BlueprintType,meta=(InlineCategoryProperty))
struct FSpellInsufficientCost : public  FGameplayTagContainer
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bInsufficientCharge = false;
};



UCLASS(BlueprintType,Blueprintable)
class USpellConditional : public UObject
{
	GENERATED_BODY()
public:
	bool Execute(USpell* Spell);
};

UCLASS(BlueprintType,Blueprintable)
class USpellCustomCost : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
    bool CheckConsume(float ConsumeScale, UPARAM(ref) FSpellInsufficientCost& Insufficient);

	UFUNCTION(BlueprintImplementableEvent)
    bool ExecuteConsume(float ConsumeScale);
};

USTRUCT(BlueprintType)
struct FMontagePlayInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* Montage;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 InstanceID;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 MontagePriority;
};
