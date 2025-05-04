// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CaAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCaAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UCaAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
