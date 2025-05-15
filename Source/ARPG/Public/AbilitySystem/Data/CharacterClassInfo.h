// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"


class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Player UMETA(DisplayName = "玩家"),
	Test UMETA(DisplayName = "测试单位"),
	GoblinWarrior UMETA(DisplayName = "哥布林战士"),
	GoblinThrower UMETA(DisplayName = "哥布林投掷手"),
	Elementalist UMETA(DisplayName = "元素师"),
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults", meta = (DisplayName = "单位主属性", ToolTip = "加载的角色主属性"))
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults",
		meta = (DisplayName = "单位技能", ToolTip = "该单位拥有的技能"))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};


/**
 * 
 */
UCLASS()
class ARPG_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
};
