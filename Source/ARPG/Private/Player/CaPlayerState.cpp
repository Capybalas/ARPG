// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CaPlayerState.h"

#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"

ACaPlayerState::ACaPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCaAbilitySystemComponent>("AbilitySystemComponent");
	// AbilitySystemComponent->SetIsReplicated(true);
	// AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UCaAttributeSet>("AttributeSet");

	// SetNetUpdateFrequency(100.f);
}

// void ACaPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
// }

UAbilitySystemComponent* ACaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
