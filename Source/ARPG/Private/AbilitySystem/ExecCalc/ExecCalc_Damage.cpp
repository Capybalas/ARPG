// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"
#include "CaGameplayTags.h"
#include "AbilitySystem/CaAbilitySystemLibrary.h"


struct CaDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);

	CaDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCaAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCaAttributeSet, MagicResistance, Target, false);
	}
};

static const CaDamageStatics& DamageStatics()
{
	static CaDamageStatics DamageStatics;
	return DamageStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	const FCaGameplayTags& GameplayTags = FCaGameplayTags::Get();

	float Damage = Spec.GetSetByCallerMagnitude(GameplayTags.AttackDamage, false, -1.f);
	float TargetArmor = 0.f;
	FGameplayEffectContextHandle ContextHandle = Spec.GetContext();
	if (Damage > 0.f)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters,
		                                                           TargetArmor);
		TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

		UCaAbilitySystemLibrary::SetDamageType(ContextHandle, GameplayTags.AttackDamage);
	}
	else
	{
		Damage = Spec.GetSetByCallerMagnitude(GameplayTags.AbilityPower, false, -1.f);

		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicResistanceDef,
		                                                           EvaluationParameters,
		                                                           TargetArmor);

		UCaAbilitySystemLibrary::SetDamageType(ContextHandle, GameplayTags.AbilityPower);
		TargetArmor = FMath::Max<float>(TargetArmor, 0.f);
	}


	Damage -= TargetArmor;
	Damage = FMath::Max<float>(1.f, Damage);
	const FGameplayModifierEvaluatedData EvaluatedData(UCaAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
