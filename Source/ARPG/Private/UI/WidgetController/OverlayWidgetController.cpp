﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/CaAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnMaxHealthChanged.Broadcast(GetCaAttributeSet()->GetMaxHealth());
	OnHealthChanged.Broadcast(GetCaAttributeSet()->GetHealth());
	OnMaxManaChanged.Broadcast(GetCaAttributeSet()->GetMaxMana());
	OnManaChanged.Broadcast(GetCaAttributeSet()->GetMana());

	OnMaxToughnessChanged.Broadcast(GetCaAttributeSet()->GetMaxToughness());
	OnToughnessChanged.Broadcast(GetCaAttributeSet()->GetToughness());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetCaAttributeSet()->GetMaxHealthAttribute()).
	                        AddLambda(
		                        [this](const FOnAttributeChangeData& Data)
		                        {
			                        OnMaxHealthChanged.Broadcast(Data.NewValue);
		                        }
	                        );

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetCaAttributeSet()->GetHealthAttribute()).
	                        AddLambda(
		                        [this](const FOnAttributeChangeData& Data)
		                        {
			                        OnHealthChanged.Broadcast(Data.NewValue);
		                        }
	                        );


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetCaAttributeSet()->GetMaxManaAttribute()).
	                        AddLambda(
		                        [this](const FOnAttributeChangeData& Data)
		                        {
			                        OnMaxManaChanged.Broadcast(Data.NewValue);
		                        }
	                        );


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetCaAttributeSet()->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetCaAttributeSet()->GetMaxToughnessAttribute()).
	                        AddLambda(
		                        [this](const FOnAttributeChangeData& Data)
		                        {
			                        OnMaxToughnessChanged.Broadcast(Data.NewValue);
		                        }
	                        );

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetCaAttributeSet()->GetToughnessAttribute()).
	                        AddLambda(
		                        [this](const FOnAttributeChangeData& Data)
		                        {
			                        OnToughnessChanged.Broadcast(Data.NewValue);
		                        }
	                        );
}
