// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LockInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULockInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API ILockInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetLock();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetLock(bool bNewState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetLockTarget(bool bNewState);
};
