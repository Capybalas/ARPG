// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CaCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "CaEnemyCharacter.generated.h"

class UBehaviorTree;
class ACaAIController;

/**
 * 
 */
UCLASS()
class ARPG_API ACaEnemyCharacter : public ACaCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	ACaEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;

	/*
	 * Enemy Interface
	 */

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;

	virtual AActor* GetCombatTarget_Implementation() const override;

	/*
	 * End Enemy Interface
	 */


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	virtual void Die(const FVector& DeathImpulse) override;
	virtual void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	virtual void ExecutedReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	virtual void StaggerReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ACaAIController> CaAIController;
};
