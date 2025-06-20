// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CaCharacterBase.h"
#include "Interface/CaPerInput.h"
#include "Interface/ExecuteInterface.h"
#include "Interface/LockInterface.h"
#include "CaPlayerCharacter.generated.h"

class UBoxComponent;
class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS(config=Game)
class ARPG_API ACaPlayerCharacter : public ACaCharacterBase, public ICaPerInput, public IExecuteInterface
{
	GENERATED_BODY()

public:
	ACaPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetLock_Implementation(bool bNewValue) override;


	/**
	 * PerInput
	 */

	virtual void SetPerInputTag_Implementation(FGameplayTag NewPerInputTag) override;
	virtual void SetCanPerInput_Implementation(bool bNewValue) override;
	virtual bool GetCanPerInput_Implementation() override;
	virtual FGameplayTag GetPerInputTag_Implementation() override;
	FGameplayTag PerInputTag;
	bool bIsPerInput;

	/**
	 * Execute 处决
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="处决")
	TObjectPtr<AActor> ExecuteTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equip")
	bool bIsCanExecute = false;

	virtual void SetExecuteActor_Implementation(AActor* Target) override;
	virtual AActor* GetExecuteActor_Implementation() override;

	virtual void SetIsCanExecute_Implementation(bool bNewValue) override;
	virtual bool GetIsCanExecute_Implementation() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> ExecuteZone;

	UFUNCTION(BlueprintCallable)
	void InExecute(AActor* InActor);

	UFUNCTION(BlueprintCallable)
	void OutExecute(AActor* OutActor);


	/**
	 * End Execute 处决
	 */


protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> CameraBoom;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	virtual void InitAbilityActorInfo() override;
};
