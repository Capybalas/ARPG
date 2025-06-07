// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CaEnemyCharacter.h"

#include "CaGameplayTags.h"
#include "AbilitySystem/CaAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"
#include "AI/CaAIController.h"
#include "UI/Widget/CaUserWidget.h"
#include "BehaviorTree/BehaviorTree.h"

ACaEnemyCharacter::ACaEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	if (GetMesh())
	{
		GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}

	AbilitySystemComponent = CreateDefaultSubobject<UCaAbilitySystemComponent>("AbilitySystemComponent");

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed;

	AttributeSet = CreateDefaultSubobject<UCaAttributeSet>("AttributeSet");

	// SelectEnemy = CreateDefaultSubobject<UWidgetComponent>(FName("SelectEnemy"));

	// SelectEnemy->SetupAttachment(GetRootComponent());

	// SelectEnemy->SetVisibility(false);
}

void ACaEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	CaAIController = Cast<ACaAIController>(NewController);
	CaAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	CaAIController->RunBehaviorTree(BehaviorTree);
	CaAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
}

void ACaEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (HasAuthority())
	{
		UCaAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}
}

void ACaEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ACaEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ACaEnemyCharacter::Die(const FVector& DeathImpulse)
{
	SetLifeSpan(LifeSpan);
	if (CaAIController) CaAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	Super::Die(DeathImpulse);
}

void ACaEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (CaAIController && CaAIController->GetBlackboardComponent())
	{
		CaAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void ACaEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UCaAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	OnASCRegistered.Broadcast(AbilitySystemComponent);
}

void ACaEnemyCharacter::InitializeDefaultAttributes() const
{
	UCaAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, 1.f, AbilitySystemComponent);
}
