// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CaAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CaGameplayTags.h"
#include "AbilitySystem/Abilities/CaGameplayAbility.h"
#include "Character/CaPlayerCharacter.h"

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
		}
	}
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

void UCaAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	if (IToughnessInterface* ToughnessInterface = Cast<IToughnessInterface>(GetAvatarActor()))
	{
		// 添加韧性恢复
		if (TSubclassOf<UGameplayEffect> ToughnessRegenEffect = ToughnessInterface->
			GetToughnessRegenEffect_Implementation())
		{
			FGameplayEffectContextHandle Context = MakeEffectContext();

			FGameplayEffectSpecHandle ToughnessSpecHandle = MakeOutgoingSpec(
				ToughnessInterface->GetToughnessRegenEffect_Implementation(),
				1,
				Context
			);

			ApplyGameplayEffectSpecToSelf(*ToughnessSpecHandle.Data);
		}

		if (TSubclassOf<UGameplayEffect> BlockRegenEffect = ToughnessInterface->
			GetToughnessBlockRegenEffect_Implementation())
		{
			ToughnessBlockRegenEffect = BlockRegenEffect;
		}
	}
}

void UCaAbilitySystemComponent::ToughnessPause_Implementation(float RecoverTime)
{
	FGameplayEffectContextHandle Context = MakeEffectContext();

	// 创建暂停 GE 实例
	FGameplayEffectSpecHandle PauseSpecHandle = MakeOutgoingSpec(
		ToughnessBlockRegenEffect,
		1,
		Context
	);

	// 设置持续时间 = ToughnessRecoverTime
	PauseSpecHandle.Data->SetSetByCallerMagnitude(
		FCaGameplayTags::Get().State_PauseToughnessRegen,
		RecoverTime
	);

	ApplyGameplayEffectSpecToSelf(*PauseSpecHandle.Data);
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
