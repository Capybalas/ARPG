#include "CaGameplayTags.h"
#include "GameplayTagsManager.h"

FCaGameplayTags FCaGameplayTags::GameplayTags;

void FCaGameplayTags::InitializeNativeGameplayTags()
{
	/** Input Tags **/
	GameplayTags.Input_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.LMB"), FString("LMB Input tags"));

	GameplayTags.Input_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.RMB"), FString("RMB Input tags"));

	GameplayTags.Input_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Shift"), FString("Shift Input tags"));
	/** End Input Tag**/


	/*
	 * Attributes
	 */

	GameplayTags.Attributes_AttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.AttackDamage"), FString("物理攻击力"));

	GameplayTags.Attributes_AbilityPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.AbilityPower"), FString("魔法攻击力"));

	GameplayTags.Attributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxHealth"),
		FString("最大生命值")
	);

	GameplayTags.Attributes_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxMana"),
		FString("最大魔法值")
	);

	GameplayTags.Attributes_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MoveSpeed"),
		FString("移动速度")
	);

	GameplayTags.Attributes_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Armor"), FString("物理防御"));

	GameplayTags.Attributes_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MagicResistance"), FString("魔法防御"));

	GameplayTags.Attributes_Toughness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Toughness"), FString("韧性"));

	GameplayTags.Attributes_MaxToughness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxToughness"), FString("最大韧性"));

	GameplayTags.Attributes_ToughnessRecoverTime = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.ToughnessRecoverTime"), FString("韧性恢复等待时间"));

	GameplayTags.Attributes_ToughnessRecoverSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.ToughnessRecoverSpeed"), FString("韧性恢复速度"));

	/**
	 * End Attributes
	 */

	/**
	 * Abilities
	 */

	GameplayTags.Abilities_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.FireBolt"), FString("Fire Bolt Ability Tag"));

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"), FString("Attack Tag"));

	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.HitReact"), FString("Hit React Tag"));

	GameplayTags.Abilities_Executed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Executed"), FString("Executed React Tag"));

	GameplayTags.Abilities_Stagger = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Stagger"), FString("Stagger React Tag"));

	GameplayTags.Abilities_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Sprint"), FString("Sprint Tag"));

	GameplayTags.Abilities_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Dodge"), FString("Dodge Tag"));

	GameplayTags.Abilities_ExecutedForwardReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.ExecutedForwardReact"), FString("Executed forward react Tag"));

	GameplayTags.Abilities_Toughness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Toughness"), FString("Toughness Tag"));

	/**
	 * End Abilities
	 */

	/** Damage Tag **/
	GameplayTags.DamageType = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.DamageType"), FString("Damage Type"));

	GameplayTags.AttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.AttackDamage"), FString("Attack Damage"));

	GameplayTags.AbilityPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.AbilityPower"), FString("Ability Power"));
	/** End Data Tag **/

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"), FString("Tag Granted when Hit Reacting"));

	GameplayTags.Effects_ExecutedReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.ExecutedReact"), FString("Tag Granted when Executed Reacting"));

	GameplayTags.Effects_ExecutedForwardReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.ExecutedForwardReact"), FString("Tag Granted when Executed Forward Reacting"));

	GameplayTags.Effects_Stagger = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Stagger"), FString("Tag Granted when Stagger Reacting"));

	GameplayTags.Effects_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Sprint"), FString("Tag Granted when Sprint"));

	GameplayTags.Effects_Toughness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Toughness"), FString("Tag Granted when Toughness"));

	GameplayTags.Effects_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Dodge"), FString("Tag Granted when Dodge"));


	/**
	 * Weapon Socket
	 */

	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Weapon"), FString("近战通过武器判定"));

	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.RightHand"), FString("近战通过右手判定"));

	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.LeftHand"), FString("近战通过左手判定"));

	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Tail"), FString("近战通过尾巴判定"));

	/*
	 * Event
	 */

	GameplayTags.Event_SprintStart = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Sprint.Start"), FString("奔跑开始"));

	GameplayTags.Event_SprintEnd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Sprint.End"), FString("奔跑结束"));

	GameplayTags.Event_Execute = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Execute"), FString("触发处决伤害"));

	/*
	 * Montage
	 */

	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"), FString("武器蒙太奇"));

	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.RightHand"), FString("武器蒙太奇"));

	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.LeftHand"), FString("武器蒙太奇"));

	/**
	 * State
	 */

	GameplayTags.State_PauseToughnessRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("State.PauseToughnessRegen"), FString("暂停韧性恢复"));

	/*
	 * Test
	 */

	GameplayTags.Test_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Test.1"), FString("测试标签1"));
}
