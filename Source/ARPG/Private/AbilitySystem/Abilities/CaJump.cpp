// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CaJump.h"

#include "Character/CaCharacterBase.h"

void UCaJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo,
                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
	{
		Character->Jump();
	}
	EndAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		true,
		false
	);
}
