#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FCaGameplayTags
{
public:
	static const FCaGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	/**
	 * Input
	 */
	FGameplayTag Input_LMB;
	FGameplayTag Input_RMB;
	FGameplayTag Input_Shift;
	/**
	 * Input End
	 */


	/**
	 * Attribute
	 */
	FGameplayTag Attributes_AttackDamage;
	FGameplayTag Attributes_AbilityPower;
	FGameplayTag Attributes_MaxHealth;
	FGameplayTag Attributes_MaxMana;
	FGameplayTag Attributes_Armor;
	FGameplayTag Attributes_MagicResistance;
	/**
	 * End Attribute
	 */

	/**
	 * Damage Tag
	 */
	FGameplayTag AttackDamage; // 物理伤害
	FGameplayTag AbilityPower; // 魔法伤害
	FGameplayTag DamageType; // 伤害类型
	/**
	 * End Damage Tag
	 */


	/**
	 * Weapon Socket
	 */
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;
	/**
	 * End Weapon Socket
	 */

	/*
	 * Abilities
	 */
	FGameplayTag Abilities_FireBolt;

	FGameplayTag Abilities_Attack;


	/*
	 * Gameplay Effects
	 */
	FGameplayTag Effects_HitReact;


	/*
	 * Montage
	 */
	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_RightHand;
	FGameplayTag Montage_Attack_LeftHand;

private:
	static FCaGameplayTags GameplayTags;
};
