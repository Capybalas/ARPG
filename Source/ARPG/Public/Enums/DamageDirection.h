// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EDamageDirection : uint8
{
	None UMETA(DisplayName = "不计算方向"),
	Front UMETA(DisplayName = "来自前方"),
	Left UMETA(DisplayName = "来自左边"),
	Right UMETA(DisplayName = "来自右边"),
	Back UMETA(DisplayName = "来自后边"),
};
