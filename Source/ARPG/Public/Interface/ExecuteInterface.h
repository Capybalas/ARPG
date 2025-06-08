// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExecuteInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UExecuteInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 处决接口
 */
class ARPG_API IExecuteInterface
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
