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
	 * Montage
	 */

	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"), FString("武器蒙太奇"));

	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.RightHand"), FString("武器蒙太奇"));

	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.LeftHand"), FString("武器蒙太奇"));
}
