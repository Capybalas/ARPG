// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CaPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CaPlayerState.h"

ACaPlayerCharacter::ACaPlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 6.f;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");;
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	/*
	 * 处决碰撞
	 */

	CharacterClass = ECharacterClass::Player;

	// 创建头部骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_00_Head = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_00_Head");
	SM_Gender_00_Head->SetupAttachment(GetMesh());

	// 创建眉毛骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_01_Eyebrows = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_01_Eyebrows");
	SM_Gender_01_Eyebrows->SetupAttachment(GetMesh());

	// 创建胡须骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_02_FacialHair = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_02_FacialHair");
	SM_Gender_02_FacialHair->SetupAttachment(GetMesh());

	// 创建上身骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_03_Torso = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_03_Torso");
	SM_Gender_03_Torso->SetupAttachment(GetMesh());

	// 创建右手臂（上）骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_04_ArmUpperRight = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_04_ArmUpperRight");
	SM_Gender_04_ArmUpperRight->SetupAttachment(GetMesh());

	// 创建左手臂（上）骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_05_ArmUpperLeft = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_05_ArmUpperLeft");
	SM_Gender_05_ArmUpperLeft->SetupAttachment(GetMesh());

	// 创建右手臂（下）骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_06_ArmLowerRight = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_06_ArmLowerRight");
	SM_Gender_06_ArmLowerRight->SetupAttachment(GetMesh());

	// 创建左手臂（下）骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_07_ArmLowerLeft = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_07_ArmLowerLeft");
	SM_Gender_07_ArmLowerLeft->SetupAttachment(GetMesh());

	// 创建右手骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_08_HandRight = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_08_HandRight");
	SM_Gender_08_HandRight->SetupAttachment(GetMesh());

	// 创建左手骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_09_HandLeft = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_09_HandLeft");
	SM_Gender_09_HandLeft->SetupAttachment(GetMesh());

	// 创建髋部骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_10_Hips = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_10_Hips");
	SM_Gender_10_Hips->SetupAttachment(GetMesh());

	// 创建右腿骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_11_LegRight = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_11_LegRight");
	SM_Gender_11_LegRight->SetupAttachment(GetMesh());

	// 创建左腿骨骼网格组件并附加到角色主骨骼网格
	SM_Gender_12_LegLeft = CreateDefaultSubobject<USkeletalMeshComponent>("SM_Gender_12_LegLeft");
	SM_Gender_12_LegLeft->SetupAttachment(GetMesh());
}

void ACaPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ACaPlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACaPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void ACaPlayerCharacter::SetLock_Implementation(bool bNewValue)
{
	Super::SetLock_Implementation(bNewValue);
	if (bNewValue)
	{
		CameraBoom->SetRelativeLocation(FVector(0.f, 60.f, 62.f));
	}
	else
	{
		CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 62.f));
	}
}

void ACaPlayerCharacter::SetPerInputTag_Implementation(FGameplayTag NewPerInputTag)
{
	PerInputTag = NewPerInputTag;
}

bool ACaPlayerCharacter::GetCanPerInput_Implementation()
{
	return bIsPerInput;
}

void ACaPlayerCharacter::SetCanPerInput_Implementation(bool bNewValue)
{
	bIsPerInput = bNewValue;
}

FGameplayTag ACaPlayerCharacter::GetPerInputTag_Implementation()
{
	return PerInputTag;
}

void ACaPlayerCharacter::SetExecuteActor_Implementation(AActor* Target)
{
	ExecuteTarget = Target;
}

AActor* ACaPlayerCharacter::GetExecuteActor_Implementation()
{
	return ExecuteTarget;
}

void ACaPlayerCharacter::SetIsCanExecute_Implementation(bool bNewValue)
{
	bIsCanExecute = bNewValue;
}

bool ACaPlayerCharacter::GetIsCanExecute_Implementation()
{
	return bIsCanExecute;
}

void ACaPlayerCharacter::InExecute(AActor* InActor)
{
	if (InActor->ActorHasTag("Enemy"))
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(InActor))
		{
			if (!CombatInterface->IsDead_Implementation() && CombatInterface->IsExecute_Implementation())
			{
				ExecuteTarget = InActor;
			}
		}
	}
}

void ACaPlayerCharacter::OutExecute(AActor* OutActor)
{
	ExecuteTarget = nullptr;
	bIsCanExecute = false;
}

void ACaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACaPlayerCharacter::InitAbilityActorInfo()
{
	ACaPlayerState* CaPlayerState = GetPlayerState<ACaPlayerState>();
	check(CaPlayerState);
	CaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(CaPlayerState, this);
	Cast<UCaAbilitySystemComponent>(CaPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = CaPlayerState->GetAbilitySystemComponent();
	AttributeSet = CaPlayerState->GetAttributeSet();
	OnASCRegistered.Broadcast(AbilitySystemComponent);

	InitializeDefaultAttributes();
}
