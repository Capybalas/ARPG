// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CaPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CaPlayerState.h"
#include "UI/Widget/CaUserWidget.h"

ACaPlayerCharacter::ACaPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 800.f;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");;
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

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
	InitializeDefaultAttributes();
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

void ACaPlayerCharacter::BeginPlay()
{
	if (UCaUserWidget* CaUserWidget = Cast<UCaUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		CaUserWidget->SetWidgetController(this);
	}

	if (const UCaAttributeSet* CaAS = Cast<UCaAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(CaAS->GetHealth());
		OnMaxHealthChanged.Broadcast(CaAS->GetMaxHealth());
	}
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
}
