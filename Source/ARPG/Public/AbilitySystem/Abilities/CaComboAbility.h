// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaDamageAbility.h"
#include "CaComboAbility.generated.h"

class ACaCharacterBase;
/**
 * 
 */
UCLASS()
class ARPG_API UCaComboAbility : public UCaDamageAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartTracing();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TraceChecking();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndTrace();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyEffectToAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	void ApplyEffectToHitActor(AActor* HitActor);

	TObjectPtr<USkeletalMeshComponent> Weapon = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Combo")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Combo")
	TArray<AActor*> Ignores;

	TArray<FHitResult> HitResults;

protected:
	TArray<FName> WeaponSocketName;
	FTimerHandle TimerHandle;
	TArray<FVector> TracePointLocations;
	TArray<AActor*> HitActorsInOneCycle;
};
