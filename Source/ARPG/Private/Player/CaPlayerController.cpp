// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CaPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CaGameplayTags.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "Character/CaCharacterBase.h"
#include "GameFramework/Character.h"
#include "Input/CaInputComponent.h"
#include "UI/Widget/DamageTextComponent.h"

ACaPlayerController::ACaPlayerController()
{
	bReplicates = true;
}

void ACaPlayerController::SetCanPerInput_Implementation(bool bNewValue)
{
	bPerInput = bNewValue;
}

FGameplayTag ACaPlayerController::GetPerInputTag_Implementation()
{
	return PerInputTag;
}

void ACaPlayerController::SetPerInputTag_Implementation(FGameplayTag NewPerInputTag)
{
	PerInputTag = NewPerInputTag;
}

void ACaPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter,
                                                          bool bCriticalHit, FGameplayTag DamageType)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(),
		                              FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bCriticalHit, DamageType);
	}
}

void ACaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputMappingContext)

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ACaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UCaInputComponent* CaInputComponent = CastChecked<UCaInputComponent>(InputComponent);
	CaInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACaPlayerController::Move);
	CaInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACaPlayerController::HandleJump);
	CaInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACaPlayerController::HandleStopJump);
	CaInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed,
	                                     &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

UCaAbilitySystemComponent* ACaPlayerController::GetASC()
{
	if (CaAbilitySystemComponent == nullptr)
	{
		CaAbilitySystemComponent = Cast<UCaAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return CaAbilitySystemComponent;
}

void ACaPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void ACaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
	if (bPerInput)
	{
		PerInputTag = InputTag;
		const FCaGameplayTags& CaGameplayTags = FCaGameplayTags();
		if (InputTag == CaGameplayTags.Input_Shift)
		{
			SetCanPerInput(false);
		}
	}
}

void ACaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

void ACaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(FVector(1, 0, 0), InputAxisVector.X);
		ControlledPawn->AddMovementInput(FVector(0, 1, 0), InputAxisVector.Y);
	}
}

void ACaPlayerController::HandleJump()
{
	if (APawn* ControlledPawn = GetPawn())
	{
		if (ACaCharacterBase* CaCharacter = Cast<ACaCharacterBase>(ControlledPawn))
		{
			CaCharacter->Jump();
		}
	}
}

void ACaPlayerController::HandleStopJump()
{
	if (APawn* ControlledPawn = GetPawn())
	{
		if (ACaCharacterBase* CaCharacter = Cast<ACaCharacterBase>(ControlledPawn))
		{
			CaCharacter->StopJumping();
		}
	}
}
