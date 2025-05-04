// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "Interface/CaPerInput.h"
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
class ARPG_API ACaPlayerController : public APlayerController, public ICaPerInput
{
	GENERATED_BODY()

public:
	ACaPlayerController();

	/**
	 * PerInput
	 */
	virtual void SetCanPerInput_Implementation(bool bNewValue) override;
	virtual FGameplayTag GetPerInputTag_Implementation() override;
	virtual void SetPerInputTag_Implementation(FGameplayTag NewTag) override;
	/**
	 * End PerInput
	 */

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bCriticalHit, FGameplayTag DamageType);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	bool bPerInput = false;
	FGameplayTag PerInputTag;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UCaInputConfig> InputConfig;

	UCaAbilitySystemComponent* GetASC();

	UPROPERTY()
	TObjectPtr<UCaAbilitySystemComponent> CaAbilitySystemComponent;

	void Move(const FInputActionValue& InputActionValue);
	void HandleJump();
	void HandleStopJump();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
