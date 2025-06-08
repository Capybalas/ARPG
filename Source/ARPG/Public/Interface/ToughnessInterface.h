// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToughnessInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UToughnessInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API IToughnessInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToughnessEffect();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveToughnessEffect();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetToughnessCooldownTimerHandle();
};
