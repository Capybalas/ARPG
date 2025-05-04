// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CaComboAbility.h"

#include "AbilitySystem/CaAbilitySystemLibrary.h"
#include "Character/CaCharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UCaComboAbility::StartTracing()
{
	const TObjectPtr<ACaCharacterBase> Character = Cast<ACaCharacterBase>(GetAvatarActorFromActorInfo());
	Weapon = Character->Weapon;
	Ignores.Empty();
	Ignores.Emplace(Character);
	TracePointLocations.Empty();
	WeaponSocketName.Empty();
	for (auto SocketName : Weapon->GetAllSocketNames())
	{
		WeaponSocketName.Emplace(SocketName);
		TracePointLocations.Emplace(Weapon->GetSocketLocation(SocketName));
	}
	HitActorsInOneCycle.Empty();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCaComboAbility::TraceChecking,
	                                       GetWorld()->DeltaTimeSeconds, true);
}

void UCaComboAbility::TraceChecking()
{
	for (int i = 0; i < WeaponSocketName.Num(); i++)
	{
		const FVector CurrentTracePointLocation = Weapon->GetSocketLocation(WeaponSocketName[i]);
		UKismetSystemLibrary::LineTraceMultiForObjects(
			GetWorld(),
			TracePointLocations[i],
			CurrentTracePointLocation,
			ObjectTypes,
			false,
			Ignores,
			EDrawDebugTrace::None,
			HitResults,
			true
		);
		TracePointLocations[i] = CurrentTracePointLocation;
		for (auto Hit : HitResults)
		{
			if (const TObjectPtr<AActor> HitActor = Hit.GetActor())
			{
				if (!HitActorsInOneCycle.Contains(HitActor))
				{
					HitActorsInOneCycle.AddUnique(HitActor);
					UCaAbilitySystemLibrary::ApplyDamageEffect(MakeDamageEffectParamsFromClassDefaults(HitActor));
				}
			}
		}
	}
}

void UCaComboAbility::EndTrace()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	HitActorsInOneCycle.Empty();
	Weapon = nullptr;
}

void UCaComboAbility::ApplyEffectToAttack()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC == nullptr) return;
	const TObjectPtr<ACaCharacterBase> Character = Cast<ACaCharacterBase>(GetAvatarActorFromActorInfo());
	TArray<TSubclassOf<UGameplayAbility>> AttackAbilities = Character->GetGameplayAbilities_Implementation();
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : AttackAbilities)
	{
		if (AbilityClass)
		{
			ASC->TryActivateAbilityByClass(AbilityClass);
		}
	}
}
