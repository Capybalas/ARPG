// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/CaWidgetController.h"

#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"
#include "Player/CaPlayerController.h"
#include "Player/CaPlayerState.h"

void UCaWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UCaWidgetController::BroadcastInitialValues()
{
}

void UCaWidgetController::BindCallbacksToDependencies()
{
}

void UCaWidgetController::BroadcastAbilityInfo()
{
}

ACaPlayerController* UCaWidgetController::GetCaPlayerController()
{
	if (CaPlayerController == nullptr)
	{
		CaPlayerController = Cast<ACaPlayerController>(PlayerController);
	}
	return CaPlayerController;
}

ACaPlayerState* UCaWidgetController::GetCaPlayerState()
{
	if (CaPlayerState == nullptr)
	{
		CaPlayerState = Cast<ACaPlayerState>(PlayerState);
	}
	return CaPlayerState;
}

UCaAbilitySystemComponent* UCaWidgetController::GetCaAbilitySystemComponent()
{
	if (CaAbilitySystemComponent == nullptr)
	{
		CaAbilitySystemComponent = Cast<UCaAbilitySystemComponent>(AbilitySystemComponent);
	}
	return CaAbilitySystemComponent;
}

UCaAttributeSet* UCaWidgetController::GetCaAttributeSet()
{
	if (CaAttributeSet == nullptr)
	{
		CaAttributeSet = Cast<UCaAttributeSet>(AttributeSet);
	}
	return CaAttributeSet;
}
