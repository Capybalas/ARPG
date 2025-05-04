// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaAbilityTypes.h"
#include "CaGameplayAbility.h"
#include "CaDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCaDamageAbility : public UCaGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage",
		meta = (DisplayName = "伤害类型"))
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage",
		meta = (DisplayName = "造成伤害", ToolTip = "影响该技能的伤害值"))
	FScalableFloat Damage;
};
