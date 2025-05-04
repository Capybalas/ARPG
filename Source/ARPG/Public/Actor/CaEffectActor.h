// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "CaEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap UMETA(DisplayName="在重叠时应用"),
	ApplyOnEndOverlap UMETA(DisplayName="在重叠结束时应用"),
	DoNotApply UMETA(DisplayName="不应用")
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class ARPG_API ACaEffectActor : public AActor
{
	GENERATED_BODY()

public:
	ACaEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "效果移除时销毁该单位", ToolTip = "当效果移除时是否销毁该对象"))
	bool bDestroyOnEffectApplication = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "对非玩家角色生效", ToolTip = "该效果是否对非玩家角色生效"))
	bool bApplyEffectToEnemies = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "瞬时效果类", ToolTip = "指定瞬时效果的类"))
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "瞬时效果应用策略", ToolTip = "瞬时效果的应用策略"))
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "持续效果类", ToolTip = "指定持续效果的类"))
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "持续效果应用策略", ToolTip = "持续效果的应用策略"))
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "无限效果类", ToolTip = "指定无限效果的类"))
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "无限效果应用策略", ToolTip = "无限效果的应用策略"))
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "无限效果移除策略", ToolTip = "无限效果的移除策略"))
	EEffectRemovePolicy InfiniteEffectRemovePolicy = EEffectRemovePolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect",
		meta = (DisplayName = "等级", ToolTip = "影响该单位的等级决策"))
	float ActorLevel = 1.f;
};
