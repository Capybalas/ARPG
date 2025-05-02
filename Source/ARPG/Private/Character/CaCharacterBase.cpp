// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CaCharacterBase.h"

#include "Components/CapsuleComponent.h"

ACaCharacterBase::ACaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), WeaponSocketName);
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

UAbilitySystemComponent* ACaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
