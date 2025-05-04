// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CaGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (DisplayName = "输入标签", ToolTip = "该技能的激活标签"))
	FGameplayTag StartupInputTag;
};
