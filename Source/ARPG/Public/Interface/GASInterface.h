// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GASInterface.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGASInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API IGASInterface
{
	GENERATED_BODY()

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const = 0;
	virtual UAttributeSet* GetAttributeSet() const = 0;
};
