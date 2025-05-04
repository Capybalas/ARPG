// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CaInputInterface.generated.h"

struct FGameplayTag;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCaInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API ICaInputInterface
{
	GENERATED_BODY()

public:
	virtual void TapInput(FGameplayTag Tag) = 0;
	virtual void PressInputStart(FGameplayTag Tag) = 0;
	virtual void PressInputComplete(FGameplayTag Tag) = 0;
	virtual void HoldInputStart(FGameplayTag Tag) = 0;
	virtual void HoldInputTriggered(FGameplayTag Tag, float DeltaTime) = 0;
	virtual void HoldInputComplete(FGameplayTag Tag) = 0;
};
