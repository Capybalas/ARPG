// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/CaUserWidget.h"

void UCaUserWidget::SetWidgetController(UObject* InWidgetController)
{
	check(InWidgetController);
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
