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

EDamageDirection UCaDamageAbility::GetHitDirection(AActor* Target, EDamageDirection InDamageDirection)
{
	const FVector AttackForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector TargetForwardVector = Target->GetActorForwardVector();

	const float DotProduct = FVector::DotProduct(AttackForwardVector, TargetForwardVector);
	const FVector CrossProduct = FVector::CrossProduct(AttackForwardVector, TargetForwardVector);

	const float Angle = FMath::RadiansToDegrees(FMath::Atan2(CrossProduct.Z, DotProduct));
	const float AngleOffset = FDamageDirectionUtils::ConvertEDamageDirectionToFloat(InDamageDirection);

	EDamageDirection Direction = FDamageDirectionUtils::ConvertFloatToEDamageDirection(Angle + AngleOffset);
	FString EnumAsString = UEnum::GetValueAsString(Direction);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, *EnumAsString);
	return Direction;
}

FDamageEffectParams UCaDamageAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor)
{
	FDamageEffectParams Params;
	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.AbilityLevel = GetAbilityLevel();
	Params.ToughnessReduction = ToughnessReduction;

	if (bIsAttack)
	{
		InitCauseDamage();
	}
	Params.BaseDamage = DamageValue == 0 ? Damage.GetValueAtLevel(GetAbilityLevel()) : DamageValue;

	Params.bIsExecute = bIsExecute;

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

	/*计算方向*/
	Params.DamageDirection = GetHitDirection(TargetActor, DamageDirection);

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
