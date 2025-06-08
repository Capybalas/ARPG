// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CaAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CaAbilityTypes.h"
#include "CaGameplayTags.h"
#include "Engine/OverlapResult.h"
#include "Game/CaGameMode.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

UCharacterClassInfo* UCaAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const ACaGameMode* CaGameModeBase = Cast<ACaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (CaGameModeBase == nullptr)
	{
		return nullptr;
	}

	return CaGameModeBase->CharacterClassInfo;
}

void UCaAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
                                                   ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;

	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.0);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

void UCaAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
                                                          ECharacterClass CharacterClass, float Level,
                                                          UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
}


FVector UCaAbilitySystemLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FCaGameplayEffectContext* CaEffectContext = static_cast<const FCaGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return CaEffectContext->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

FGameplayTag UCaAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FCaGameplayEffectContext* CaEffectContext = static_cast<const FCaGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		if (CaEffectContext->GetDamageType().IsValid())
		{
			return *CaEffectContext->GetDamageType();
		}
	}
	return FGameplayTag();
}

bool UCaAbilitySystemLibrary::GetIsAttack(FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FCaGameplayEffectContext* CaEffectContext = static_cast<const FCaGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return CaEffectContext->GetIsAttack();
	}
	return false;
}

//
// bool UCaAbilitySystemLibrary::GetIsExecute(FGameplayEffectContextHandle& EffectContextHandle)
// {
// 	if (const FCaGameplayEffectContext* CaEffectContext = static_cast<const FCaGameplayEffectContext*>(
// 		EffectContextHandle.Get()))
// 	{
// 		return CaEffectContext->GetIsExecute();
// 	}
// 	return false;
// }

bool UCaAbilitySystemLibrary::GetIsExecute(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FCaGameplayEffectContext* CaEffectContext = static_cast<const FCaGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return CaEffectContext->GetIsExecute();
	}
	return false;
}

void UCaAbilitySystemLibrary::SetIsExecute(FGameplayEffectContextHandle& EffectContextHandle, const bool InIsExecute)
{
	if (FCaGameplayEffectContext* CaEffectContext = static_cast<FCaGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		CaEffectContext->SetIsExecute(InIsExecute);
	}
}

void UCaAbilitySystemLibrary::SetIsAttack(FGameplayEffectContextHandle& EffectContextHandle, const bool InIsAttack)
{
	if (FCaGameplayEffectContext* CaEffectContext = static_cast<FCaGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		CaEffectContext->SetIsAttack(InIsAttack);
	}
}

void UCaAbilitySystemLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,
                                              const FVector& InImpulse)
{
	if (FCaGameplayEffectContext* CaEffectContext = static_cast<FCaGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		CaEffectContext->SetDeathImpulse(InImpulse);
	}
}

bool UCaAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FCaGameplayEffectContext* CaGameplayEffectContext = static_cast<const FCaGameplayEffectContext*>(
		EffectContextHandle.
		Get()))
	{
		return CaGameplayEffectContext->IsCriticalHit();
	}
	return false;
}

void UCaAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle EffectContextHandle,
                                               bool bInIsCriticalHit)
{
	if (FCaGameplayEffectContext* CaGameplayEffectContext = static_cast<FCaGameplayEffectContext*>(EffectContextHandle.
		Get()))
	{
		CaGameplayEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

bool UCaAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;

	return !bFriends;
}

void UCaAbilitySystemLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContextHandle,
                                            const FGameplayTag InDamageType)
{
	if (FCaGameplayEffectContext* CaEffectContext = static_cast<FCaGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		CaEffectContext->SetDamageType(DamageType);
	}
}

FGameplayEffectContextHandle UCaAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->
	                                                                      MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);
	SetIsExecute(EffectContextHandle, DamageEffectParams.bIsExecute);
	SetIsAttack(EffectContextHandle, DamageEffectParams.bIsAttack);
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(
		DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType,
	                                                              DamageEffectParams.BaseDamage);


	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContextHandle;
}

void UCaAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
                                                         TArray<AActor*>& OutOverlappingActors,
                                                         const TArray<AActor*>& ActorsToIgnore, float Radius,
                                                         const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
	                                                             EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity,
		                                FCollisionObjectQueryParams(
			                                FCollisionObjectQueryParams::InitType::AllDynamicObjects),
		                                FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(
				Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}
