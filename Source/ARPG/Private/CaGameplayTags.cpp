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

	GameplayTags.Abilities_Execute = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Execute"), FString("Execute React Tag"));

	GameplayTags.Abilities_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Sprint"), FString("Sprint Tag"));

	GameplayTags.Abilities_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Dodge"), FString("Dodge Tag"));

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

	GameplayTags.Effects_ExecuteReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.ExecuteReact"), FString("Tag Granted when Execute Reacting"));

	GameplayTags.Effects_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Sprint"), FString("Tag Granted when Sprint"));


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

	/*
	 * Montage
	 */

	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"), FString("武器蒙太奇"));

	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.RightHand"), FString("武器蒙太奇"));

	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.LeftHand"), FString("武器蒙太奇"));
}
