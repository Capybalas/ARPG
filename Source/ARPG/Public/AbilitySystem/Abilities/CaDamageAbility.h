// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaAbilityTypes.h"
#include "CaGameplayAbility.h"
#include "Interface/CombatInterface.h"
#include "CaDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCaDamageAbility : public UCaGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void InitCauseDamage();

	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr);

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage",
		meta = (DisplayName = "攻击伤害"))
	bool bIsAttack = false;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage",
		meta=(DisplayName = "伤害效果类"))
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage",
		meta=(DisplayName = "削韧效果类"))
	TSubclassOf<UGameplayEffect> ToughnessEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage",
		meta = (DisplayName = "伤害类型"))
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage",
		meta = (DisplayName = "造成伤害", ToolTip = "影响该技能的伤害值"))
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage",
		meta = (DisplayName = "死亡冲量", ToolTip = "该技能造成死亡时对死亡单位造成的物理冲击力"))
	float DeathImpulseMagnitude = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage",
		meta = (DisplayName = "冲量弧度", ToolTip = "该技能造成伤害时，受伤单位会被击飞到什么方向"))
	float AttackImpulse = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category="Damage",
		meta = (DisplayName = "击飞角度"))
	float Pitch = 10.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage",
		meta = (DisplayName = "削韧"))
	float ToughnessReduction = 0.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Damage",
		meta = (DisplayName = "是处决伤害"))
	bool bIsExecute = false;

private:
	float DamageValue = 0.f;
};
