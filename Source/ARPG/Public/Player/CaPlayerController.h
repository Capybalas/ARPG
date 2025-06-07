// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "Interface/CombatInterface.h"
#include "CaPlayerController.generated.h"

/**
 * 
 */

class UDamageTextComponent;
class UCaInputConfig;
class UInputAction;
class UInputMappingContext;
class UCaAbilitySystemComponent;

UCLASS()
class ARPG_API ACaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACaPlayerController();

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bCriticalHit, FGameplayTag DamageType);
	FVector2D MovementVector;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Config")
	float LockRadius = 1200.f;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LockAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> DodgeOrSprintAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UCaInputConfig> InputConfig;

	UCaAbilitySystemComponent* GetASC();

	UPROPERTY()
	TObjectPtr<UCaAbilitySystemComponent> CaAbilitySystemComponent;

	void Move(const FInputActionValue& InputActionValue);
	void DodgeOrSprintStart(const FInputActionInstance& InputActionValue);
	void DodgeOrSprintEnd(const FInputActionInstance& InputActionValue);
	void Dodge(const FInputActionInstance& InputActionValue);
	void MoveReleased();
	void LockTarget();

	void HandleJump();
	void HandleStopJump();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
