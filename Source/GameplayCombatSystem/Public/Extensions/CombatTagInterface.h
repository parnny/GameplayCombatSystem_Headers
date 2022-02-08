// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatTagInterface.generated.h"

#define IMPLEMENT_COMBAT_GAMEPLAY_TAG_BODY(ClassName, MemberName) \
	FGameplayTagContainer& ClassName##::GetGameplayTagContainer() \
	{ \
		return MemberName; \
	} \
	void ClassName##::AddGameplayTag(const FGameplayTag& Tag) \
	{ \
		if (Tag.IsValid()) \
		{ \
			MemberName.AddTag(Tag); \
			PostGameplayTagChanged(Tag,false); \
		} \
	} \
	void ClassName##::AddGameplayTag(const FName TagName) \
	{ \
		const FGameplayTag& FindTag = FGameplayTag::RequestGameplayTag(TagName,false); \
		AddGameplayTag(FindTag); \
	} \
	void ClassName##::RemoveGameplayTag(const FGameplayTag& Tag, bool bDeferParentTags) \
	{ \
		if (Tag.IsValid()) \
		{ \
			if (MemberName.IsValid()) \
			{ \
				MemberName.RemoveTag(Tag,bDeferParentTags); \
				PostGameplayTagChanged(Tag,true); \
			} \
		} \
	} \
	void ClassName##::RemoveGameplayTag(const FName TagName, bool bDeferParentTags) \
	{ \
		const FGameplayTag& FindTag = FGameplayTag::RequestGameplayTag(TagName,false); \
		RemoveGameplayTag(FindTag, bDeferParentTags); \
	} \
	bool ClassName##::HasGameplayTag(const FGameplayTag& Tag, bool Exact) const \
	{ \
		if (Tag.IsValid()) \
		{ \
			if (MemberName.IsValid()) \
			{ \
				return Exact ? MemberName.HasTagExact(Tag) : MemberName.HasTag(Tag); \
			} \
		} \
		return false; \
	} \
	bool ClassName##::HasGameplayTag(const FName TagName, bool Exact) const \
	{ \
		const FGameplayTag& FindTag = FGameplayTag::RequestGameplayTag(TagName,true); \
		return HasGameplayTag(FindTag,Exact); \
	} \
	bool ClassName##::BP_HasGameplayTag(const FGameplayTag Tag, bool Exact) const \
	{ \
		return HasGameplayTag(Tag,Exact); \
	}


// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UCombatTagInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAYCOMBATSYSTEM_API ICombatTagInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FGameplayTagContainer& GetGameplayTagContainer() = 0;
	
	virtual void AddGameplayTag(const FGameplayTag& Tag) = 0;
	virtual void AddGameplayTag(const FName TagName) = 0;
	UFUNCTION(BlueprintCallable, meta=(DisplayName="AddGameplayTag"))
	virtual void BP_AddGameplayTag(const FGameplayTag Tag);
	
	virtual void RemoveGameplayTag(const FGameplayTag& Tag, bool bDeferParentTags) = 0;
	virtual void RemoveGameplayTag(const FName TagName, bool bDeferParentTags) = 0;
	UFUNCTION(BlueprintCallable, meta=(DisplayName="RemoveGameplayTag"))
	virtual void BP_RemoveGameplayTag(const FGameplayTag Tag, bool bDeferParentTags);

	virtual bool HasGameplayTag(const FGameplayTag& Tag, bool Exact) const = 0;
	virtual bool HasGameplayTag(const FName TagName, bool Exact) const = 0;
	virtual bool BP_HasGameplayTag(const FGameplayTag Tag, bool Exact) const = 0;

	virtual void PostGameplayTagChanged(const FGameplayTag Tag, bool bRemove) = 0;
};
