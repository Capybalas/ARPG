#pragma once
#include "GameplayEffectTypes.h"
#include "CaAbilityTypes.generated.h"


class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	// 构造函数
	FDamageEffectParams()
	{
	}

	// 蓝图可读写的属性，表示该伤害效果的上下文对象，通常用于获取与伤害相关的世界信息
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WorldContextObject = nullptr;

	// 蓝图可读写的属性，表示伤害效果的 GameplayEffect 类型，用于定义伤害的具体效果
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	// 蓝图可读写的属性，表示伤害来源的 AbilitySystemComponent，用于确定伤害的施加者
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	// 蓝图可读写的属性，表示伤害目标的 AbilitySystemComponent，用于确定伤害的承受者
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	// 蓝图可读写的属性，表示基础伤害值，是伤害计算的基础数值
	UPROPERTY(BlueprintReadWrite)
	float BaseDamage = 0.f;

	// 蓝图可读写的属性，表示技能等级，可能用于影响伤害值的计算
	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel = 1.f;

	// 蓝图可读写的属性，表示伤害类型，用于区分不同类型的伤害（例如物理伤害、魔法伤害等）
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag DamageType = FGameplayTag();

	// 蓝图可读写的属性，表示施加负面效果（Debuff）的概率，范围为 0 到 1
	UPROPERTY(BlueprintReadWrite)
	float DebuffChance = 0.f;

	// 蓝图可读写的属性，表示负面效果的伤害值
	UPROPERTY(BlueprintReadWrite)
	float DebuffDamage = 0.f;

	// 蓝图可读写的属性，表示负面效果的持续时间
	UPROPERTY(BlueprintReadWrite)
	float DebuffDuration = 0.f;

	// 蓝图可读写的属性，表示负面效果的触发频率
	UPROPERTY(BlueprintReadWrite)
	float DebuffFrequency = 0.f;

	// 蓝图可读写的属性，表示死亡冲击的强度，用于在目标死亡时施加冲击力
	UPROPERTY(BlueprintReadWrite)
	float DeathImpulseMagnitude = 0.f;

	// 蓝图可读写的属性，表示死亡冲击的方向和大小
	UPROPERTY(BlueprintReadWrite)
	FVector DeathImpulse = FVector::ZeroVector;

	// 蓝图可读写的属性，表示是否为范围伤害，用于区分单体伤害和范围伤害
	UPROPERTY(BlueprintReadWrite)
	bool bIsRadialDamage = false;

	// 蓝图可读写的属性，表示范围伤害的内半径，用于定义伤害范围的内部边界
	UPROPERTY(BlueprintReadWrite)
	float RadialDamageInnerRadius = 0.f;

	// 蓝图可读写的属性，表示范围伤害的外半径，用于定义伤害范围的外部边界
	UPROPERTY(BlueprintReadWrite)
	float RadialDamageOuterRadius = 0.f;

	// 蓝图可读写的属性，表示范围伤害的中心点，用于确定伤害范围的位置
	UPROPERTY(BlueprintReadWrite)
	FVector RadialDamageOrigin = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAttack = false;


	UPROPERTY(BlueprintReadWrite)
	bool bIsExecute = false;
};


USTRUCT(BlueprintType)
struct FCaGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsSuccessfulDebuff() const { return bIsSuccessfulDebuff; }
	float GetDebuffDamage() const { return DebuffDamage; }
	float GetDebuffDuration() const { return DebuffDuration; }
	float GetDebuffFrequency() const { return DebuffFrequency; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }
	FVector GetDeathImpulse() const { return DeathImpulse; }
	bool IsRadialDamage() const { return bIsRadialDamage; }
	float GetRadialDamageInnerRadius() const { return RadialDamageInnerRadius; }
	float GetRadialDamageOuterRadius() const { return RadialDamageOuterRadius; }
	FVector GetRadialDamageOrigin() const { return RadialDamageOrigin; }
	bool GetIsAttack() const { return bIsAttack; }
	bool GetIsExecute() const { return bIsExecute; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsSuccessfulDebuff(bool bInIsDebuff) { bIsSuccessfulDebuff = bInIsDebuff; }
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }
	void SetDebuffFrequency(float InFrequency) { DebuffFrequency = InFrequency; }
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; }
	void SetDeathImpulse(const FVector& InImpulse) { DeathImpulse = InImpulse; }
	void SetIsRadialDamage(bool bInIsRadialDamage) { bIsRadialDamage = bInIsRadialDamage; }
	void SetIsAttack(bool bInIsAttack) { bIsAttack = bInIsAttack; }
	void SetIsExecute(bool bInIsExecute) { bIsExecute = bInIsExecute; }

	void SetRadialDamageInnerRadius(float InRadialDamageInnerRadius)
	{
		RadialDamageInnerRadius = InRadialDamageInnerRadius;
	}

	void SetRadialDamageOuterRadius(float InRadialDamageOuterRadius)
	{
		RadialDamageOuterRadius = InRadialDamageOuterRadius;
	}

	void SetRadialDamageOrigin(const FVector& InRadialDamageOrigin) { RadialDamageOrigin = InRadialDamageOrigin; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	// virtual FCaGameplayEffectContext* Duplicate() const
	// {
	// 	FCaGameplayEffectContext* NewContext = new FCaGameplayEffectContext();
	// 	*NewContext = *this;
	// 	if (GetHitResult())
	// 	{
	// 		// Does a deep copy of the hit result
	// 		NewContext->AddHitResult(*GetHitResult(), true);
	// 	}
	//
	// 	return NewContext;
	// }

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;

	TSharedPtr<FGameplayTag> DamageType;

	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

	UPROPERTY()
	bool bIsRadialDamage = false;

	UPROPERTY()
	float RadialDamageInnerRadius = 0.f;

	UPROPERTY()
	float RadialDamageOuterRadius = 0.f;

	UPROPERTY()
	FVector RadialDamageOrigin = FVector::ZeroVector;

	UPROPERTY()
	bool bIsAttack = false;

	UPROPERTY()
	bool bIsExecute = false;
};
