// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatWorldObject.generated.h"

/**
 * 慎用
 * 这个类的Outer必须可以追溯到 WorldContext
 * GetWorld 的实现参考AActor
 * 这个类存在的意义是为了让 战斗插件某些类(Ex:Spell,Aura,Effect)可以轻松的访问需要WorldContext的接口(Ex:GetPlayerController,SpawnActor)
 */
UCLASS(Abstract)
class GAMEPLAYCOMBATSYSTEM_API UCombatWorldObject : public UObject
{
	GENERATED_UCLASS_BODY()

	virtual UWorld* GetWorld() const override;
};
