// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "CaCharacterBase.generated.h"

class UNiagaraSystem;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UAnimMontage;
class UNiagaraComponent;


UCLASS(Abstract)
class ARPG_API ACaCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACaCharacterBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	UPROPERTY(BlueprintReadOnly, Category="Combat",
		meta = (DisplayName = "初始移速", ToolTip = "该角色的默认移动速度"))
	float BaseWalkSpeed = 450.f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(EditAnywhere, Category="Combat",
		meta = (DisplayName = "连招动画", ToolTip = "普通攻击的蒙太奇"))
	UAnimMontage* ComboMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	FName WeaponHandSocket = FName("weapon_socket_r");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon",
		meta = (DisplayName = "左手伤害判定点", ToolTip = "怪物武器的判定点"))
	FName LeftHandTipSocketName = FName("left_hand_socket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon",
		meta = (DisplayName = "右手伤害判定点", ToolTip = "怪物武器的判定点"))
	FName RightHandTipSocketName = FName("right_hand_socket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon",
		meta = (DisplayName = "尾巴伤害判定点", ToolTip = "怪物武器的判定点"))
	FName TailSocketName = FName("");

	virtual TArray<TSubclassOf<UGameplayAbility>> GetGameplayAbilities_Implementation() const;

	/**
	 * Combo Interface
	 */

	virtual void SetIsBeingShocked_Implementation(bool bInShock) override;
	virtual bool IsBeingShocked_Implementation() const override;

	virtual void Die(const FVector& DeathImpulse) override;
	virtual bool IsDead_Implementation() const override;
	virtual USkeletalMeshComponent* GetWeapon_Implementation() override;
	virtual FOnASCRegistered GetOnASCRegisteredDelegate() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	FOnASCRegistered OnASCRegistered;


	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void StartWeaponNiagara_Implementation() override;
	virtual void EndWeaponNiagara_Implementation() override;

	/**
	 * End Combo Interface
	 */
	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bIsBeingShocked = false;
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpulse);

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> HealthBar;


	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	virtual void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat",
		meta = (DisplayName = "死亡声音", ToolTip = "死亡时播放音效"))
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	void AddCharacterAbilities();
	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attribute")
	TSubclassOf<UGameplayEffect> DefaultAttribute;
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Info")
	ECharacterClass CharacterClass = ECharacterClass::GoblinWarrior;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Niagara")
	TObjectPtr<UNiagaraSystem> WeaponNiagaraSystem;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> AttackAbilities;
};
