// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CaPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CaPlayerState.h"


ACaPlayerCharacter::ACaPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 1000.f;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");;
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
}

void ACaPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void ACaPlayerCharacter::InitAbilityActorInfo()
{
	ACaPlayerState* CaPlayerState = GetPlayerState<ACaPlayerState>();
	check(CaPlayerState);
	CaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(CaPlayerState, this);
	AbilitySystemComponent = CaPlayerState->GetAbilitySystemComponent();
	AttributeSet = CaPlayerState->GetAttributeSet();
}
