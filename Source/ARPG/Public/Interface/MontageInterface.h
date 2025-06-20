// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/DamageDirection.h"
#include "MontageInterface.generated.h"

UINTERFACE()
class UMontageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API IMontageInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetExecutionMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetToBeExterminated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetExecutionMontageForward();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetToBeExterminatedForward();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();
};
