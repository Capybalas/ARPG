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
	// CaAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	CaAIController->RunBehaviorTree(BehaviorTree);
	// CaAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);

	// CaAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),
	//                                                          CharacterClass != ECharacterClass::GoblinWarrior);
}

void ACaEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UCaAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}


	if (UCaUserWidget* CaUserWidget = Cast<UCaUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		CaUserWidget->SetWidgetController(this);
	}

	if (const UCaAttributeSet* CaAS = Cast<UCaAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CaAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CaAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FCaGameplayTags::Get().Effects_HitReact,
		                                                 EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ACaEnemyCharacter::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(CaAS->GetHealth());
		OnMaxHealthChanged.Broadcast(CaAS->GetMaxHealth());
	}
}

void ACaEnemyCharacter::Die(const FVector& DeathImpulse)
{
	SetLifeSpan(LifeSpan);
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
