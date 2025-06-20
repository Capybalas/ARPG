// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Enums/DamageDirection.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UNiagaraSystem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*)

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};

USTRUCT(BlueprintType)
struct FCombo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "伤害倍数", ToolTip = "本次攻击造成攻击力的多少倍伤害"))
	float DamageMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "冲击力", ToolTip = "该伤害对目标造成的冲击力"))
	float Impact = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "架势韧性", ToolTip = "出招时临时获得的韧性"))
	float ComboToughness = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "蒙太奇速率", ToolTip = "播放该蒙太奇的速率"))
	float MontageRate = 1.f;
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	// 纯虚函数，用于获取 Weapon

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USkeletalMeshComponent* GetWeapon();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;


	virtual void Die(const FVector& DeathImpulse) = 0;
	virtual FOnASCRegistered GetOnASCRegisteredDelegate() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsBeingShocked() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsBeingShocked(bool bInShock);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetCombatMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<TSubclassOf<UGameplayAbility>> GetAttackAbilities() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartWeaponNiagara();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndWeaponNiagara();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartSprinting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopSprinting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetMoveSpeed(float NewSpeed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCombatTarget(AActor* NewTarget);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetCombatTarget();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetLockOnVisibility(bool bIsDisplayLockIcon);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDodgeDirection(FName Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName GetDodgeDirection();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetDodgeMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsExecute();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FCombo GetComboData(int32 ComboIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EDamageDirection GetDamageDirection();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDamageDirection(EDamageDirection InDamageDirection);
};
