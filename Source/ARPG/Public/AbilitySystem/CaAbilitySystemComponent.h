// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interface/CaPerInput.h"
#include "Interface/ToughnessInterface.h"
#include "CaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCaAbilitySystemComponent : public UAbilitySystemComponent, public ICaPerInput,
                                           public IToughnessInterface
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	bool bStartupAbilitiesGiven = false;

	/*
	 * 韧性系统
	 */

	void AddToughnessEffect_Implementation() override;
	void RemoveToughnessEffect_Implementation() override;
	void ResetToughnessCooldownTimerHandle_Implementation() override;

protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	                         FActiveGameplayEffectHandle ActiveEffectHandle);
};
