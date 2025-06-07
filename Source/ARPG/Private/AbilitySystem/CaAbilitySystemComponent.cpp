// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CaAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CaGameplayTags.h"
#include "AbilitySystem/Abilities/CaGameplayAbility.h"
#include "Character/CaPlayerCharacter.h"
#include "Game/CaGameMode.h"
#include "Kismet/GameplayStatics.h"

// 按住
void UCaAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
}

// 松下按键
void UCaAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

// 按下按键
void UCaAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FGameplayTagContainer TagsToActivate;
	TagsToActivate.AddTag(InputTag);
	TryActivateAbilitiesByTag(TagsToActivate, true);
	if (ICaPerInput* PerInput = Cast<ICaPerInput>(GetAvatarActor()))
	{
		if (PerInput->GetCanPerInput_Implementation())
		{
			PerInput->SetPerInputTag_Implementation(InputTag);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,
			                                 FString::Printf(TEXT("InputTag: %s"), *InputTag.ToString()));
		}
	}


	// for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	// {
	// 	if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
	// 	{
	// 		AbilitySpecInputPressed(AbilitySpec);
	// 		if (!AbilitySpec.IsActive())
	// 		{
	// 			TryActivateAbilitiesByTag()
	// 			TryActivateAbility(AbilitySpec.Handle);
	// 			if (bIsPerInput)
	// 			{
	// 				PerInputTag = InputTag;	
	// 			}
	// 		}
	// 	}
	// }
}

void UCaAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UCaGameplayAbility* CaAbility = Cast<UCaGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(CaAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
	bStartupAbilitiesGiven = true;
}

void UCaAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UCaAbilitySystemComponent::ClientEffectApplied);
}

void UCaAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                   const FGameplayEffectSpec& EffectSpec,
                                                                   FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
}
