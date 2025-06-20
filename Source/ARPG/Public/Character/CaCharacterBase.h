// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "Interface/LockInterface.h"
#include "Interface/MontageInterface.h"
#include "Enums/DamageDirection.h"
#include "Interface/ToughnessInterface.h"
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
class ARPG_API ACaCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface,
                                  public IToughnessInterface, public ILockInterface, public IMontageInterface
{
	GENERATED_BODY()

public:
	ACaCharacterBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Weapon",
		meta = (DisplayName = "武器附加点"))
	FName WeaponHandSocket = FName("weapon_socket_r");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Weapon",
		meta = (DisplayName = "武器附加点"))
	FName WeaponTipSocketName = FName("s1");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Weapon",
		meta = (DisplayName = "左手伤害判定点", ToolTip = "武器的判定点"))
	FName LeftHandTipSocketName = FName("left_hand_socket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Weapon",
		meta = (DisplayName = "右手伤害判定点", ToolTip = "武器的判定点"))
	FName RightHandTipSocketName = FName("right_hand_socket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Weapon",
		meta = (DisplayName = "尾巴伤害判定点", ToolTip = "武器的判定点"))
	FName TailSocketName = FName("");


	// 其他
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	// State
	UPROPERTY(BlueprintReadWrite, Category = "Combat|State")
	bool bIsLocking = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat",
		meta = (DisplayName = "可以触发处决", ToolTip = "该属性为真时，则不需要削韧即可在敌人后方触发处决"))
	bool bIsExecute = true;

	UPROPERTY(BlueprintReadOnly, Category="Combat|State",
		meta = (DisplayName = "初始移速", ToolTip = "该角色的默认移动速度"))
	float BaseWalkSpeed = 450.f;

	UPROPERTY(BlueprintReadOnly, Category="Combat|State",
		meta = (DisplayName = "最大移动速度", ToolTip = "该角色的最大移动速度"))
	float MaxWalkSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat",
		meta = (DisplayName = "奔跑状态"))
	bool bIsSprinting = false;

	// Montage
	UPROPERTY(EditAnywhere, Category = "Combat|Montage",
		meta = (DisplayName = "连招动画", ToolTip = "普通攻击的蒙太奇"))
	UAnimMontage* ComboMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Montage",
		meta = (DisplayName = "闪避动画", ToolTip = "若某方向动画不存在，则使用就近的动画"))
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Montage", meta = (DisplayName = "处决动画"))
	UAnimMontage* ExecutionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Montage", meta = (DisplayName = "被处决动画"))
	UAnimMontage* ToBeExterminated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Montage", meta = (DisplayName = "前方处决动画"))
	UAnimMontage* ExecutionMontageForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Montage", meta = (DisplayName = "前方被处决动画"))
	UAnimMontage* ToBeExterminatedForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Montage", meta = (DisplayName = "受击动画"))
	TMap<EDamageDirection, UAnimMontage*> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Data")
	TArray<FCombo> ComboData;

	UPROPERTY(EditDefaultsOnly, Category = "韧性",
		meta=(DisplayName = "韧性恢复效果"))
	TSubclassOf<UGameplayEffect> ToughnessRegenEffect;

	UPROPERTY(EditDefaultsOnly, Category = "韧性",
		meta=(DisplayName = "阻止韧性恢复效果"))
	TSubclassOf<UGameplayEffect> ToughnessBlockRegenEffect;

	UPROPERTY()
	FName DodgeDirection = "B";

	UPROPERTY()
	EDamageDirection DamageDirection;

	virtual TArray<TSubclassOf<UGameplayAbility>> GetGameplayAbilities_Implementation() const;

	/**
	 * Combat Interface
	 */

	virtual void SetIsBeingShocked_Implementation(bool bInShock) override;
	virtual bool IsBeingShocked_Implementation() const override;

	virtual void Die(const FVector& DeathImpulse) override;
	virtual bool IsDead_Implementation() const override;
	virtual USkeletalMeshComponent* GetWeapon_Implementation() override;
	virtual FOnASCRegistered GetOnASCRegisteredDelegate() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	FOnASCRegistered OnASCRegistered;

	virtual TArray<FTaggedMontage> GetAttackMontage_Implementation() override;
	virtual UAnimMontage* GetCombatMontage_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;

	virtual void StartWeaponNiagara_Implementation() override;
	virtual void EndWeaponNiagara_Implementation() override;

	virtual AActor* GetAvatar_Implementation() override;

	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual void StartSprinting_Implementation() override;
	virtual void StopSprinting_Implementation() override;
	virtual void SetCombatTarget_Implementation(AActor* NewTarget) override;
	virtual AActor* GetCombatTarget_Implementation() override;
	virtual void SetLock_Implementation(bool bNewValue) override;
	virtual bool GetLock_Implementation() override;
	virtual void LockTarget_Implementation();
	virtual void SetLockOnVisibility_Implementation(bool bIsDisplayLockIcon) override;

	virtual void SetDodgeDirection_Implementation(FName NewDirection) override;
	virtual FName GetDodgeDirection_Implementation() override;
	virtual UAnimMontage* GetDodgeMontage_Implementation() override;
	virtual bool IsExecute_Implementation() override;
	virtual FCombo GetComboData_Implementation(int32 ComboIndex) override;

	virtual void SetDamageDirection_Implementation(EDamageDirection InDamageDirection) override;
	virtual EDamageDirection GetDamageDirection_Implementation() override;

	/**
	 * End Combat Interface
	 */

	/*
	 * 韧性系统
	 */
	virtual TSubclassOf<UGameplayEffect> GetToughnessBlockRegenEffect_Implementation() override;
	virtual TSubclassOf<UGameplayEffect> GetToughnessRegenEffect_Implementation() override;
	void OnMoveSpeedAttributeChanged(const float Value);

	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bIsBeingShocked = false;
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpulse);

	UPROPERTY(BlueprintReadOnly, Category="Combat|State")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat|State")
	bool bExecutedReacting = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat|State")
	bool bStaggerReacting = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat|Montage")
	TArray<FTaggedMontage> AttackMontages;


	/*
	 * MontageInterface
	 */

	virtual UAnimMontage* GetExecutionMontage_Implementation() override;
	virtual UAnimMontage* GetToBeExterminated_Implementation() override;
	virtual UAnimMontage* GetExecutionMontageForward_Implementation() override;
	virtual UAnimMontage* GetToBeExterminatedForward_Implementation() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	/*
	 * End MontageInterface
	 */


protected:
	virtual void BeginPlay() override;
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> HealthBar;


	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMoveSpeedChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnToughnessChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxToughnessChanged;

	virtual void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void ExecutedReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void StaggerReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

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

	UPROPERTY(EditDefaultsOnly, Category = "Niagara")
	TObjectPtr<UNiagaraSystem> WeaponNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* BloodEffect;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> AttackAbilities;
};
