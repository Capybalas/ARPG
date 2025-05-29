// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CaCharacterBase.h"

#include "CaGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystem/CaAbilitySystemComponent.h"
#include "AbilitySystem/CaAttributeSet.h"
#include  "ARPG/ARPG.h"
#include "Components/WidgetComponent.h"

ACaCharacterBase::ACaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon"));
	Weapon->SetupAttachment(GetMesh(), WeaponHandSocket);
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	HealthBar = CreateDefaultSubobject<UWidgetComponent>(FName("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
}

void ACaCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UAbilitySystemComponent* ACaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<TSubclassOf<UGameplayAbility>> ACaCharacterBase::GetGameplayAbilities_Implementation() const
{
	return AttackAbilities;
}

void ACaCharacterBase::SetIsBeingShocked_Implementation(bool bInShock)
{
	bIsBeingShocked = bInShock;
}

bool ACaCharacterBase::IsBeingShocked_Implementation() const
{
	return bIsBeingShocked;
}

void ACaCharacterBase::Die(const FVector& DeathImpulse)
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	// 死亡时移除血条
	if (HealthBar)
	{
		HealthBar->DestroyComponent();
		HealthBar == nullptr;
	}
	MulticastHandleDeath(DeathImpulse);
}

bool ACaCharacterBase::IsDead_Implementation() const
{
	return bIsDead;
}

USkeletalMeshComponent* ACaCharacterBase::GetWeapon_Implementation()
{
	return Weapon;
}

FOnASCRegistered ACaCharacterBase::GetOnASCRegisteredDelegate()
{
	return OnASCRegistered;
}

FVector ACaCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FCaGameplayTags& GameplayTags = FCaGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}

	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandTipSocketName);
	}

	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandTipSocketName);
	}

	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}

	return FVector();
}

TArray<FTaggedMontage> ACaCharacterBase::GetAttackMontage_Implementation()
{
	return AttackMontages;
}

UAnimMontage* ACaCharacterBase::GetCombatMontage_Implementation()
{
	return ComboMontage;
}

FTaggedMontage ACaCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

UAnimMontage* ACaCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ACaCharacterBase::StartWeaponNiagara_Implementation()
{
	ICombatInterface::StartWeaponNiagara_Implementation();
}

void ACaCharacterBase::EndWeaponNiagara_Implementation()
{
	ICombatInterface::EndWeaponNiagara_Implementation();
}

AActor* ACaCharacterBase::GetAvatar_Implementation()
{
	return this;
}

UNiagaraSystem* ACaCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

void ACaCharacterBase::MulticastHandleDeath_Implementation(const FVector& DeathImpulse)
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Weapon->AddImpulse(DeathImpulse * 0.1f, NAME_None, true);

	// 启用角色网格（通常是角色的视觉模型）的物理模拟
	GetMesh()->SetSimulatePhysics(true);

	// 启用角色网格的重力，使角色受到重力影响
	GetMesh()->SetEnableGravity(true);

	// 设置角色网格的碰撞模式为仅物理碰撞
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	// 设置角色网格对“世界静态”碰撞通道的响应为“阻挡”，这意味着角色网格会与世界中的静态物体（如地形、建筑等）发生物理碰撞
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetMesh()->AddImpulse(DeathImpulse, NAME_None, true);

	// 禁用角色的胶囊碰撞组件的碰撞，胶囊碰撞组件通常用于角色的碰撞检测和移动，这里将其碰撞关闭
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsDead = true;

	// OnDeathDelegate.Broadcast(this);
}

void ACaCharacterBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
}

void ACaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetMesh(), AttachmentRules, WeaponHandSocket);
}

void ACaCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	UCaAbilitySystemComponent* ASC = CastChecked<UCaAbilitySystemComponent>(AbilitySystemComponent);
	ASC->AddCharacterAbilities(StartupAbilities);
	ASC->AddCharacterAbilities(AttackAbilities);
}

void ACaCharacterBase::InitAbilityActorInfo()
{
}

void ACaCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ACaCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultAttribute, 1.f);
}
