// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CaPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CaGameplayTags.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "Character/CaCharacterBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/CaInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widget/DamageTextComponent.h"

ACaPlayerController::ACaPlayerController()
{
	bReplicates = true;
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

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ACaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UCaInputComponent* CaInputComponent = CastChecked<UCaInputComponent>(InputComponent);
	CaInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACaPlayerController::Move);
	CaInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ACaPlayerController::MoveReleased);
	CaInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACaPlayerController::MoveReleased);

	CaInputComponent->BindAction(DodgeOrSprintAction, ETriggerEvent::Triggered, this,
	                             &ACaPlayerController::DodgeOrSprintStart);
	CaInputComponent->BindAction(DodgeOrSprintAction, ETriggerEvent::Completed, this,
	                             &ACaPlayerController::DodgeOrSprintEnd);
	CaInputComponent->BindAction(DodgeOrSprintAction, ETriggerEvent::Canceled, this,
	                             &ACaPlayerController::Dodge);

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
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagPressed(InputTag);
}

void ACaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ACaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
}

void ACaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (APawn* PlayerPawn = GetPawn())
	{
		MovementVector = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0, GetControlRotation().Yaw, 0);
		if (MovementVector.X != 0.f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			PlayerPawn->AddMovementInput(MovementDirection, MovementVector.X);
		}

		if (MovementVector.Y != 0.f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			PlayerPawn->AddMovementInput(MovementDirection, MovementVector.Y);
		}
	}
}

void ACaPlayerController::DodgeOrSprintStart(const FInputActionInstance& InputActionValue)
{
	if (GetASC() == nullptr) return;
	if (MovementVector.X > 0.f || MovementVector.Y > 0.f)
	{
		FGameplayTagContainer TagsToActivate;
		TagsToActivate.AddTag(FCaGameplayTags::Get().Abilities_Sprint);
		GetASC()->TryActivateAbilitiesByTag(TagsToActivate);
	}
	else
	{
		DodgeOrSprintEnd(InputActionValue);
	}
}

void ACaPlayerController::DodgeOrSprintEnd(const FInputActionInstance& InputActionValue)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), FCaGameplayTags::Get().Event_SprintEnd,
	                                                         FGameplayEventData());
}

void ACaPlayerController::Dodge(const FInputActionInstance& InputActionValue)
{
	if (GetCharacter()->GetCharacterMovement()->IsFalling()) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetPawn());
	FName DodgeDirection = "D";
	if (MovementVector.X != 0 || MovementVector.Y != 0)
	{
		float Dir = UKismetMathLibrary::MakeRotFromX(FVector(MovementVector.Y, MovementVector.X, 0)).Yaw;
		Dir = FMath::UnwindRadians(FMath::DegreesToRadians(Dir));
		Dir = FMath::RadiansToDegrees(Dir);

		if (FMath::Abs(Dir) <= 30.f)
		{
			DodgeDirection = "F";
		}
		else if (Dir > 30.f && Dir <= 60.f)
		{
			DodgeDirection = "FR";
		}
		else if (Dir > 60.f && Dir <= 130.f)
		{
			DodgeDirection = "R";
		}
		else if (Dir > 130.f && Dir <= 160.f)
		{
			DodgeDirection = "BR";
		}
		else if (Dir < -30.f && Dir >= -60.f)
		{
			DodgeDirection = "FL";
		}
		else if (Dir < -60.f && Dir >= -130.f)
		{
			DodgeDirection = "L";
		}
		else if (Dir < -130.f && Dir >= -160.f)
		{
			DodgeDirection = "BL";
		}
		else
		{
			DodgeDirection = "B";
		}
	}
	CombatInterface->SetDodgeDirection_Implementation(DodgeDirection);
	FGameplayTagContainer TagsToActivate;
	TagsToActivate.AddTag(FCaGameplayTags::Get().Abilities_Dodge);
	GetASC()->TryActivateAbilitiesByTag(TagsToActivate);
}

void ACaPlayerController::MoveReleased()
{
	MovementVector = FVector2d::ZeroVector;
}

void ACaPlayerController::LockTarget()
{
	// if (ACharacter* PlayerActor = GetCharacter())
	// {
	// 	if (PlayerCombatInterface)
	// 	{
	// 		if (!PlayerCombatInterface->GetLock_Implementation())
	// 		{
	// 			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	// 			ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	// 			TArray<AActor*> Ignores;
	// 			Ignores.Add(PlayerActor);
	// 			TArray<AActor*> OverlappingPawns;
	// 			UKismetSystemLibrary::SphereOverlapActors(
	// 				PlayerActor,
	// 				PlayerActor->GetActorLocation(),
	// 				LockRadius,
	// 				ObjectTypes,
	// 				ACaEnemyCharacter::StaticClass(),
	// 				Ignores,
	// 				OverlappingPawns
	// 			);
	// 			DrawDebugSphere(
	// 				GetWorld(),
	// 				PlayerActor->GetActorLocation(),
	// 				LockRadius,
	// 				12,
	// 				FColor::Red,
	// 				false,
	// 				5.0f
	// 			);
	//
	// 			FCollisionQueryParams QueryParams;
	// 			QueryParams.AddIgnoredActor(this);
	// 			TMap<AActor*, float> TargetWithDistance;
	//
	// 			for (AActor* HitActor : OverlappingPawns)
	// 			{
	// 				if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(HitActor))
	// 				{
	// 					if (!CombatInterface->IsDead_Implementation())
	// 					{
	// 						FHitResult HitResult;
	// 						GetWorld()->LineTraceSingleByChannel(
	// 							HitResult,
	// 							PlayerActor->GetActorLocation(),
	// 							HitActor->GetActorLocation(),
	// 							ECC_Visibility,
	// 							QueryParams
	// 						);
	//
	//
	// 						DrawDebugLine(
	// 							GetWorld(),
	// 							PlayerActor->GetActorLocation(),
	// 							HitActor->GetActorLocation(),
	// 							FColor::Red,
	// 							false,
	// 							5.0f,
	// 							0,
	// 							2.0f
	// 						);
	//
	//
	// 						if (HitResult.GetActor() == HitActor)
	// 						{
	// 							TargetWithDistance.Add(HitActor, PlayerActor->GetDistanceTo(HitActor));
	// 						}
	// 					}
	// 				}
	// 			}
	//
	// 			if (TargetWithDistance.Num() == 0) return;
	// 			float MinDistance = TNumericLimits<float>::Max();
	// 			AActor* LockTarget = nullptr;
	// 			for (const auto& Target : TargetWithDistance)
	// 			{
	// 				if (Target.Value < MinDistance)
	// 				{
	// 					MinDistance = Target.Value;
	// 					LockTarget = Target.Key;
	// 				}
	// 			}
	//
	// 			if (IsValid(LockTarget))
	// 			{
	// 				PlayerCombatInterface->SetCombatTarget_Implementation(LockTarget);
	// 				PlayerCombatInterface->SetLock_Implementation(true);
	// 				DrawDebugSphere(
	// 					GetWorld(),
	// 					LockTarget->GetActorLocation(),
	// 					60.f,
	// 					12,
	// 					FColor::Green,
	// 					false,
	// 					5.0f
	// 				);
	// 			}
	// 			else
	// 			{
	// 				// 当范围内没有可锁定的单位时
	// 				PlayerCombatInterface->SetLock_Implementation(false);
	// 			}
	// 		}
	// 		else
	// 		{
	// 			PlayerCombatInterface->SetLock_Implementation(false);
	// 		}
	// 	}
	// }
}


void ACaPlayerController::HandleJump()
{
	if (ACharacter* PlayerActor = GetCharacter())
	{
		PlayerActor->Jump();
	}
}

void ACaPlayerController::HandleStopJump()
{
	if (ACharacter* PlayerActor = GetCharacter())
	{
		PlayerActor->StopJumping();
	}
}
