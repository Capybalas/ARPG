// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CaAbilitySystemComponent.h"
#include "Data/CharacterClassInfo.h"
#include "Interface/CombatInterface.h"
#include "CaAbilitySystemLibrary.generated.h"

struct FDamageEffectParams;
/**
 * 
 */
UCLASS()
class ARPG_API UCaAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
	                                 ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass,
	                                        float Level, UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary|GameplayEffects")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AbilitySystemLibrary|GameplayEffects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|GameplayEffects")
	static bool GetIsAttack(UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary|GameplayEffects")
	static bool GetIsExecute(const FGameplayEffectContextHandle& EffectContextHandle);


	/*
	 * Set
	 */

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|GameplayEffects")
	static void SetDeathImpulse(UPARAM(ref)
	                            FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);

	UFUNCTION(BlueprintPure, Category="AbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref)
	                             FGameplayEffectContextHandle EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|GameplayEffects")
	static void SetDamageType(UPARAM(ref)
	                          FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag InDamageType);

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|GameplayEffects")
	static void SetIsAttack(UPARAM(ref)
	                        FGameplayEffectContextHandle& EffectContextHandle, bool InIsAttack);

	UFUNCTION(BlueprintCallable, Category="AbilitySystemLibrary|GameplayEffects")
	static void SetIsExecute(UPARAM(ref)
	                         FGameplayEffectContextHandle& EffectContextHandle, bool InIsExecute);


	UFUNCTION(BlueprintCallable, Category = "AbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

	/*
	 * Gameplay Mechanics
	 */

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors,
	                                       const TArray<AActor*>& ActorsToIgnore, float Radius,
	                                       const FVector& SphereOrigin);
};
