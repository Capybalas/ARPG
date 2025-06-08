// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CaAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CaGameplayTags.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/CaAbilitySystemLibrary.h"
#include "Character/CaCharacterBase.h"
#include "Interface/CombatInterface.h"
#include "Net/UnrealNetwork.h"
#include "Player/CaPlayerController.h"

UCaAttributeSet::UCaAttributeSet()
{
	const FCaGameplayTags& GameplayTags = FCaGameplayTags::Get();


	TagsToAttributes.Add(GameplayTags.Attributes_AttackDamage, GetAttackDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_AbilityPower, GetAbilityPowerAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MaxMana, GetManaAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MagicResistance, GetMagicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MoveSpeed, GetMoveSpeedAttribute);
}

void UCaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, AbilityPower, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, Health, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UCaAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UCaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Props.TargetCharacter->Implements<UCombatInterface>() &&
		ICombatInterface::Execute_IsDead(Props.TargetCharacter))
		return;

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleIncomingDamage(Props);
	}
}

void UCaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetMaxHealthAttribute())
	{
		SetHealth(GetMaxHealth());
	}
	
	if (Attribute == GetMaxManaAttribute())
	{
		SetMana(GetMaxMana());
	}

	if (Attribute == GetToughnessAttribute())
	{
		SetToughness(GetMaxToughness());
	}
}

void UCaAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->
		AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UCaAttributeSet::HandleIncomingDamage(const FEffectProperties& Props)
{
	// 获取即将受到的伤害值，并将其重置为0
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);

	// 如果即将受到的伤害值大于0，则进行处理
	if (LocalIncomingDamage > 0.f)
	{
		// 计算新的生命值，并确保其在0到最大生命值之间
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
		// 判断是否致命

		if (NewHealth <= 0.f)
		{
			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor))
			{
				CombatInterface->Die(UCaAbilitySystemLibrary::GetDeathImpulse(Props.EffectContextHandle));
			}
		}
		else
		{
			if (Props.TargetCharacter->Implements<UCombatInterface>())
			{
				FGameplayTagContainer TagContainer;
				if (UCaAbilitySystemLibrary::GetIsExecute(Props.EffectContextHandle))
				{
					if (ICombatInterface::Execute_IsExecute(Props.TargetCharacter))
					{
						TagContainer.AddTag(FCaGameplayTags::Get().Effects_ExecutedReact);
					}
				}
				else if (!ICombatInterface::Execute_IsBeingShocked(Props.TargetCharacter))
				{
					TagContainer.AddTag(FCaGameplayTags::Get().Effects_HitReact);
				}
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}


		}
		const bool bCriticalHit = UCaAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		const FGameplayTag DamageType = UCaAbilitySystemLibrary::GetDamageType(Props.EffectContextHandle);
		ShowFloatingText(Props, LocalIncomingDamage, bCriticalHit, DamageType);
	}
}

void UCaAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bCriticalHit,
                                       FGameplayTag DamageType) const
{
	if (!IsValid(Props.SourceCharacter) || !IsValid(Props.TargetCharacter)) return;
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (ACaPlayerController* PC = Cast<ACaPlayerController>(Props.SourceCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bCriticalHit, DamageType);
			return;
		}
		if (ACaPlayerController* PC = Cast<ACaPlayerController>(Props.TargetCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bCriticalHit, DamageType);
		}
	}
}
