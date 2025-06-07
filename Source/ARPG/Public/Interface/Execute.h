// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Execute.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UExecute : public UInterface
{
	GENERATED_BODY()
};

/**
 * 处决接口
 */
class ARPG_API IExecute
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetExecuteActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetExecuteActor(AActor* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsCanExecute(bool bNewValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsCanExecute();
};
