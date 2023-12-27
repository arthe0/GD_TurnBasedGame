// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Attributes/TBGCharacterAttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"

UTBGCharacterAttributeSet::UTBGCharacterAttributeSet()
{
	Health = 100.f;
	Mana = 100.f;
}

// Attribute change functions
void UTBGCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttributeOnChange(Attribute, NewValue);
}

void UTBGCharacterAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttributeOnChange(Attribute, NewValue);
}

void UTBGCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UTBGCharacterAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

bool UTBGCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UTBGCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

// Replication functions
void UTBGCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Health
	DOREPLIFETIME_CONDITION_NOTIFY(UTBGCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UTBGCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)

	// Mana
	DOREPLIFETIME_CONDITION_NOTIFY(UTBGCharacterAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UTBGCharacterAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
}

void UTBGCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBGCharacterAttributeSet, Health, Old);
}

void UTBGCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBGCharacterAttributeSet, MaxHealth, Old);
}

void UTBGCharacterAttributeSet::OnRep_Mana(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBGCharacterAttributeSet, Mana, Old);
}

void UTBGCharacterAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& Old)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBGCharacterAttributeSet, MaxMana, Old);
}

// Helper methods
void UTBGCharacterAttributeSet::ClampAttributeOnChange(const FGameplayAttribute& AffectedAttribute, float& NewValue) const
{
	if(AffectedAttribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	if(AffectedAttribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
	}
}		


