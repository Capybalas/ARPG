// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EDamageDirection : uint8
{
	Forward UMETA(DisplayName = "来自前方"),
	Back UMETA(DisplayName = "来自后方"),
	Left UMETA(DisplayName = "来自左侧"),
	Right UMETA(DisplayName = "来自右侧"),
	ForwardLeft UMETA(DisplayName = "来自前左"),
	ForwardRight UMETA(DisplayName = "来自前右"),
	BackLeft UMETA(DisplayName = "来自后左"),
	BackRight UMETA(DisplayName = "来自后右")
};

class ARPG_API FDamageDirectionUtils
{
public:
	static float ConvertEDamageDirectionToFloat(EDamageDirection Direction);
	static EDamageDirection ConvertFloatToEDamageDirection(float Angle);
};
