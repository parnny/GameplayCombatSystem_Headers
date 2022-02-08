// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "CombatVariable.generated.h"

class UCombatVariableReader;
class ICombatVariableInterface;

UENUM(BlueprintType)
enum class ECombatVariableType : uint8
{
	Scalar,
	Variable,
	Curve,
	DataTable,
	Property,
	Function,
};

USTRUCT(BlueprintType)
struct FCombatVariable_Float
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECombatVariableType Type = ECombatVariableType::Scalar;

	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::Scalar"))
	float Scalar;

	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::Variable"))
	FName Variable;

	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::Curve"))
	TSoftObjectPtr<UCurveFloat> Curve;

	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::Curve"))
	float CurveKey;
	
	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::DataTable"))
	TSoftObjectPtr<UDataTable> DataTable;
	
	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::DataTable"))
	FName RowName;
	
	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::DataTable"))
	FName ColumnName;
	
	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::Property"))
	FName Property;
	
	UPROPERTY(EditAnywhere, meta = (editcondition = "Type == ECombatVariableType::Function"))
	FName Function;
};

UCLASS(BlueprintType,Blueprintable)
class UCombatVariableContainer : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleInstanceOnly)
	UCombatVariableContainer* Parent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName,FCombatVariable_Float> SharedCombatVariables;

	UFUNCTION(BlueprintPure)
	float GetFloat(FName Key, bool& Found);

	float GetFloat_Internal(FName Key, bool& Found, int32& Deep);
	float GetFloat_Internal(const FCombatVariable_Float* CV_Float, bool& Found, int32& Deep);
	
};
