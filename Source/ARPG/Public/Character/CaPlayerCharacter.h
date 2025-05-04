// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CaCharacterBase.h"
#include "CaPlayerCharacter.generated.h"

class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS(config=Game)
class ARPG_API ACaPlayerCharacter : public ACaCharacterBase
{
	GENERATED_BODY()

public:
	ACaPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equip")
	// TObjectPtr<USkeletalMeshComponent> SM_All_00_HeadCoverings_NoHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_00_Head; // 头

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_01_Eyebrows; // 眉毛

	// 胡须
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_02_FacialHair;

	// 上身
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_03_Torso;

	// 右手臂（上）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_04_ArmUpperRight;

	// 左手臂（上）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_05_ArmUpperLeft;

	// 右手臂（下）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_06_ArmLowerRight;

	// 左手臂（下）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_07_ArmLowerLeft;

	// 右手
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_08_HandRight;

	// 左手
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_09_HandLeft;

	// 髋部
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_10_Hips;

	// 右腿
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_11_LegRight;

	// 左腿
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	TObjectPtr<USkeletalMeshComponent> SM_Gender_12_LegLeft;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;


	virtual void InitAbilityActorInfo() override;
};
