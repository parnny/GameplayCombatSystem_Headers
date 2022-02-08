// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraPolicy.generated.h"

class UAura;
UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UAuraApplyPolicy : public UObject
{
	GENERATED_BODY()
public:
	virtual bool AuraApply(UAura* Aura, float& Lifetime, int32& Stack) const;
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="AuraApply"))
	void BP_AuraApply(UAura* Aura, float InLifetime, int32 InStack, float& OutLifetime, int32& OutStack) const;
};






UCLASS(Blueprintable,BlueprintType)
class GAMEPLAYCOMBATSYSTEM_API UAuraRefreshPolicy : public UObject
{
	GENERATED_BODY()
public:
	virtual void AuraRefresh(UAura* Aura, float& Lifetime, int32& Stack) const;
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="AuraRefresh"))
	void BP_AuraRefresh(UAura* Aura, float InLifetime, int32 InStack, float& OutLifetime, int32& OutStack) const;
};

UCLASS(Blueprintable)
class GAMEPLAYCOMBATSYSTEM_API UAuraRefreshPolicy_Extend : public UAuraRefreshPolicy
{
	GENERATED_BODY()
public:
	virtual void AuraRefresh(UAura* Aura, float& Lifetime, int32& Stack) const override;
};

UCLASS(Blueprintable)
class GAMEPLAYCOMBATSYSTEM_API UAuraRefreshPolicy_Override : public UAuraRefreshPolicy
{
	GENERATED_BODY()
public:
	virtual void AuraRefresh(UAura* Aura, float& Lifetime, int32& Stack) const override;
};
