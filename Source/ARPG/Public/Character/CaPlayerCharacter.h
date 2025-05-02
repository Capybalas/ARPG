// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaCharacterBase.h"
#include "CaPlayerCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ARPG_API ACaPlayerCharacter : public ACaCharacterBase
{
	GENERATED_BODY()

public:
	ACaPlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	// virtual void OnRep_PlayerState() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	void InitAbilityActorInfo();
};
