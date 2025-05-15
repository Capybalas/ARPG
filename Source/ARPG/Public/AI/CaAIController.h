// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CaAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class ARPG_API ACaAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACaAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
