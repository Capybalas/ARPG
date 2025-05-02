// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CaInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FCaInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class ARPG_API UCaInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCaInputAction> AbilityInputActions;
};
