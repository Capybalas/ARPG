// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CaDamageAbility.h"
#include "AbilitySystemBlueprintLibrary.h"


FDamageEffectParams UCaDamageAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor) const
{
	FDamageEffectParams Params;
	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.AbilityLevel = GetAbilityLevel();
	Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	Params.DamageType = DamageType;
	return Params;
}
