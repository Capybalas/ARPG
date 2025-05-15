// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CaDamageAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CaGameplayTags.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"

void UCaDamageAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType, DamageValue);
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

void UCaDamageAbility::InitCauseDamage()
{
	const FCaGameplayTags GameplayTag = FCaGameplayTags::Get();
	const UCaAbilitySystemComponent* ASC = Cast<UCaAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	const UCaAttributeSet* AttributeSet = ASC->GetSet<UCaAttributeSet>();

	DamageValue = DamageType.MatchesTag(GameplayTag.AttackDamage)
		              ? AttributeSet->GetAttackDamage()
		              : AttributeSet->GetAbilityPower();
}

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


FTaggedMontage UCaDamageAbility::GetRandomTaggedMontageFromArray(
	const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() > 0)
	{
		return TaggedMontages[FMath::RandRange(0, TaggedMontages.Num() - 1)];
	}
	return FTaggedMontage();
}
