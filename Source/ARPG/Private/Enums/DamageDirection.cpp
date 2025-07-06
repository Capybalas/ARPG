// Fill out your copyright notice in the Description page of Project Settings.


#include "Enums/DamageDirection.h"

float FDamageDirectionUtils::ConvertEDamageDirectionToFloat(EDamageDirection Direction)
{
	switch (Direction)
	{
	case EDamageDirection::Forward:
		return 0.0f;
	case EDamageDirection::ForwardRight:
		return 22.5f;
	case EDamageDirection::Right:
		return 45.0f;
	case EDamageDirection::BackRight:
		return 67.5f;
	case EDamageDirection::Back:
		return 90.0f;
	case EDamageDirection::BackLeft:
		return 112.5f;
	case EDamageDirection::Left:
		return 135.0f;
	case EDamageDirection::ForwardLeft:
		return 157.5f;
	default:
		return 0.0f;
	}
}

EDamageDirection FDamageDirectionUtils::ConvertFloatToEDamageDirection(float Angle)
{
	// Normalize the angle to be within 0 to 360 degrees
	Angle = FMath::Fmod(Angle, 360.0f);
	if (Angle < 0.0f)
	{
		Angle += 360.0f;
	}

	// Convert the angle to the new range
	Angle = 180.0f - Angle;

	// Adjust the angle to be within -180 to 180 degrees
	if (Angle > 180.0f)
	{
		Angle -= 360.0f;
	}

	// Determine the direction based on the adjusted angle
	if (Angle >= -22.5f && Angle < 22.5f)
	{
		return EDamageDirection::Forward;
	}
	if (Angle >= 22.5f && Angle < 67.5f)
	{
		return EDamageDirection::ForwardRight;
	}
	if (Angle >= 67.5f && Angle < 112.5f)
	{
		return EDamageDirection::Right;
	}
	if (Angle >= 112.5f && Angle < 157.5f)
	{
		return EDamageDirection::BackRight;
	}
	if (Angle >= 157.5f || Angle < -157.5f)
	{
		return EDamageDirection::Back;
	}
	if (Angle >= -157.5f && Angle < -112.5f)
	{
		return EDamageDirection::BackLeft;
	}
	if (Angle >= -112.5f && Angle < -67.5f)
	{
		return EDamageDirection::Left;
	}
	if (Angle >= -67.5f && Angle < -22.5f)
	{
		return EDamageDirection::ForwardLeft;
	}

	return EDamageDirection::Forward;
}
