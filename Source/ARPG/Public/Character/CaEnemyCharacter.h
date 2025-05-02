// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaCharacterBase.h"
#include "CaEnemyCharacter.generated.h"

UCLASS()
class ARPG_API ACaEnemyCharacter : public ACaCharacterBase
{
	GENERATED_BODY()

public:
	ACaEnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
