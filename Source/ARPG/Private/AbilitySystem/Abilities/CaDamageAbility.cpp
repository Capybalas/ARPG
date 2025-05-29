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
	Params.BaseDamage = DamageValue == 0 ? Damage.GetValueAtLevel(GetAbilityLevel()) : DamageValue;
	if (AttackImpulse != 0)
	{
		const FRotator Rotation(0, AttackImpulse, 0);
		Params.DeathImpulse = FQuat(Rotation).RotateVector(GetAvatarActorFromActorInfo()->GetActorForwardVector()) *
			DeathImpulseMagnitude;
	}
	else
	{
		Params.DeathImpulse = GetAvatarActorFromActorInfo()->GetActorForwardVector() * DeathImpulseMagnitude;
	}
	Params.DamageType = DamageType;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;
	Params.KnockbackChance = KnockbackChance;
	Params.KnockbackForceMagnitude = KnockbackForceMagnitude;
	if (FMath::RandRange(1, 100) < Params.KnockbackChance)
	{
		FRotator Rotation = GetAvatarActorFromActorInfo()->GetActorRotation();
		Rotation.Pitch = Pitch;
		const FVector KnockbackDirection = Rotation.Vector();
		Params.KnockbackForce = KnockbackDirection * KnockbackForceMagnitude;
	}

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
