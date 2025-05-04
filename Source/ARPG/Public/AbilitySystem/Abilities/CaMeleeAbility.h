// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaDamageAbility.h"
#include "CaMeleeAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCaMeleeAbility : public UCaDamageAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	void StartTracing();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	void TraceChecking();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	void TraceCheck(bool bIsStart);
};
