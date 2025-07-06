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
	FGameplayTag Attributes_MoveSpeed;
	FGameplayTag Attributes_Armor;
	FGameplayTag Attributes_MagicResistance;
	FGameplayTag Attributes_Toughness;
	FGameplayTag Attributes_MaxToughness;
	FGameplayTag Attributes_ToughnessRecoverTime;
	FGameplayTag Attributes_ToughnessRecoverSpeed;
	FGameplayTag Attributes_StunThreshold;


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
	FGameplayTag Abilities_HitReact;
	FGameplayTag Abilities_Executed;
	FGameplayTag Abilities_Stagger;
	FGameplayTag Abilities_Sprint;
	FGameplayTag Abilities_Dodge;
	FGameplayTag Abilities_ExecutedForwardReact;
	FGameplayTag Abilities_Toughness;

	/*
	 * Gameplay Effects
	 */
	FGameplayTag Effects_HitReact;
	FGameplayTag Effects_ExecutedReact;
	FGameplayTag Effects_Stagger;
	FGameplayTag Effects_Sprint;
	FGameplayTag Effects_ExecutedForwardReact;
	FGameplayTag Effects_Toughness;
	FGameplayTag Effects_Dodge;

	/*
	 * Event
	 */

	FGameplayTag Event_SprintStart;
	FGameplayTag Event_SprintEnd;
	FGameplayTag Event_Execute;


	/*
	 * Montage
	 */
	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_RightHand;
	FGameplayTag Montage_Attack_LeftHand;

	/**
	 * State
	 */

	FGameplayTag State_PauseToughnessRegen;

	/**
	 * Test
	 */

	FGameplayTag Test_1;

private:
	static FCaGameplayTags GameplayTags;
};
