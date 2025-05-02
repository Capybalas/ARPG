// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CaPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Input/CaEnhancedInputComponent.h"

ACaPlayerController::ACaPlayerController()
{
}

void ACaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(InputComponent, TEXT("Can't find InputComponent"));

	check(InputMappingContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());

	Subsystem->AddMappingContext(InputMappingContext, 0);


	// check(CaContext);
	// UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
	// 	GetLocalPlayer());
	//
	// if (Subsystem)
	// {
	// 	Subsystem->AddMappingContext(CaContext, 0);
	// }
	//
	//
	// bShowMouseCursor = true;
	// DefaultMouseCursor = EMouseCursor::Default;
	//
	// FInputModeGameAndUI InputModeData;
	// InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// InputModeData.SetHideCursorDuringCapture(false);
	// SetInputMode(InputModeData);
}

void ACaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UCaEnhancedInputComponent* CaInputComponent = CastChecked<UCaEnhancedInputComponent>(InputComponent);

	CaInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACaPlayerController::Move);
}

void ACaPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void ACaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
}

void ACaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
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
