// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CaPerInput.generated.h"

// This class does not need to be modified.

UINTERFACE(Blueprintable, MinimalAPI)
class UCaPerInput : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API ICaPerInput
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCanPerInput(bool bNewValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetCanPerInput();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FGameplayTag GetPerInputTag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPerInputTag(FGameplayTag NewPerInputTag);
};
