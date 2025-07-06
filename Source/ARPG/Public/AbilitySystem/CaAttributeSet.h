// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() = default;

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class ARPG_API UCaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCaAttributeSet();
	// virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	TMap<FGameplayTag, FGameplayAttribute (*)()> TagsToAttributes;
	/**
	 * 主要属性
	 */

	// Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, Health);

	// MaxHealth
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, MaxHealth);

	// Mana
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, Mana);

	// MaxMana
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, MaxMana);

	// MoveSpeed
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, MoveSpeed);

	// AttackDamage
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, AttackDamage);

	// Armor
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, Armor);

	// AbilityPower
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData AbilityPower;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, AbilityPower);

	// MagicResistance
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, MagicResistance);

	// 韧性
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Toughness;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, Toughness);

	// 最大韧性
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxToughness;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, MaxToughness);

	// 韧性恢复等待时间
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ToughnessRecoverTime;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, ToughnessRecoverTime);

	// 韧性恢复速度
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ToughnessRecoverSpeed;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, ToughnessRecoverSpeed);

	// 踉跄阈值
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData StunThreshold;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, StunThreshold);

	/**
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UCaAttributeSet, IncomingDamage)

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	void HandleIncomingDamage(const FEffectProperties& Props);
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bCriticalHit,
	                      FGameplayTag DamageType) const;
};
