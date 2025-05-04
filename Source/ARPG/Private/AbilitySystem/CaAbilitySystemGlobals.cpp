// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CaAbilitySystemGlobals.h"

#include "CaAbilityTypes.h"

FGameplayEffectContext* UCaAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FCaGameplayEffectContext();
}
