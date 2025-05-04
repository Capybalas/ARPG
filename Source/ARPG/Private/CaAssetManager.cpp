// Fill out your copyright notice in the Description page of Project Settings.


#include "CaAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "CaGameplayTags.h"

UCaAssetManager& UCaAssetManager::Get()
{
	check(GEngine);
	UCaAssetManager* CaAssetManager = Cast<UCaAssetManager>(GEngine->AssetManager);
	return *CaAssetManager;
}

void UCaAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FCaGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
