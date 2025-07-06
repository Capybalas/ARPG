// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CaAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CaGameplayTags.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/CaAbilitySystemLibrary.h"
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

	TagsToAttributes.Add(GameplayTags.Attributes_Toughness, GetToughnessAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MaxToughness, GetMaxToughnessAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_ToughnessRecoverTime, GetToughnessRecoverTimeAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_ToughnessRecoverSpeed, GetToughnessRecoverSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_StunThreshold, GetStunThresholdAttribute);
}

// void UCaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, Armor, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);

// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, AbilityPower, COND_None, REPNOTIFY_Always);

// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, Health, COND_None, REPNOTIFY_Always);

// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);

// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, Toughness, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, MaxToughness, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, ToughnessRecoverSpeed, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, ToughnessRecoverTime, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UCaAttributeSet, StunThreshold, COND_None, REPNOTIFY_Always);
// }

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

	if (Attribute == GetToughnessAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxToughness());
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

	if (Attribute == GetMaxToughnessAttribute())
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
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
		// 判断是否致命
		if (NewHealth <= 0.f)
		{
			if (CombatInterface)
			{
				CombatInterface->Die(UCaAbilitySystemLibrary::GetDeathImpulse(Props.EffectContextHandle));
			}
		}
		else
		{
			const FCaGameplayTags& GameplayTags = FCaGameplayTags::Get();
			const float ToughnessReduction = UCaAbilitySystemLibrary::GetToughnessReduction(
				Props.EffectContextHandle);


			// 不处于处决状态时
			if (!Props.TargetASC->HasMatchingGameplayTag(GameplayTags.Effects_Stagger))
			{
				// 削韧大于0且不是处决伤害
				if (ToughnessReduction > 0.f && !UCaAbilitySystemLibrary::GetIsExecute(Props.EffectContextHandle))
				{
					FGameplayTagContainer TagContainer;
					float NewToughness = GetToughness() - ToughnessReduction;
					if (NewToughness <= 0.f)
					{
						// 硬直状态
						TagContainer.AddTag(GameplayTags.Effects_Stagger);
						NewToughness = GetMaxToughness();
					}
					// 削韧值超过阈值时触发踉跄 或者 削韧超过当前阈值的 50%
					else if (ToughnessReduction > GetStunThreshold() || ToughnessReduction > GetToughness() * 0.5f)
					{
						if (CombatInterface)
						{
							CombatInterface->SetDamageDirection_Implementation(
								UCaAbilitySystemLibrary::GetDamageDirection(Props.EffectContextHandle));
						}
						TagContainer.AddTag(GameplayTags.Effects_HitReact);
					}
					// 存在削韧
					Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
					SetToughness(NewToughness);
				}
			}

			if (IToughnessInterface* ToughnessInterface = Cast<IToughnessInterface>(Props.TargetASC))
			{
				ToughnessInterface->ToughnessPause_Implementation(GetToughnessRecoverTime());
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
