// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CaEnemyCharacter.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"


ACaEnemyCharacter::ACaEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UCaAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	// AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	// AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UCaAttributeSet>("AttributeSet");
}

void ACaEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
