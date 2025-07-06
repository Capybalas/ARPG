// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaDamageAbility.h"
#include "DrawDebugHelpers.h"
#include "CaComboAbility.generated.h"

class ACaCharacterBase;
/**
 * 
 */
UCLASS()
class ARPG_API UCaComboAbility : public UCaDamageAbility
{
	GENERATED_BODY()
	UCaComboAbility();

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartTracing();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TraceChecking();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndTrace();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyEffectToAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
	void ApplyEffectToHitActor(AActor* HitActor);

	TObjectPtr<USkeletalMeshComponent> Weapon = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Combo",
		meta = (DisplayName = "碰撞检测通道", ToolTip = "射线检测的通道"))
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Combo",
		meta = (DisplayName = "无视角色", ToolTip = "碰撞时无视的角色"))
	TArray<AActor*> Ignores;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Combo",
		meta = (DisplayName = "连招数据"))
	FCombo ComboData;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Combo",
		meta = (DisplayName = "显示测试信息"))
	bool bIsShowDebug = false;


	TArray<FHitResult> HitResults;

protected:
	TArray<FName> WeaponSocketName;
	FTimerHandle TimerHandle;
	TArray<FVector> TracePointLocations;
	TArray<AActor*> HitActorsInOneCycle;
};
