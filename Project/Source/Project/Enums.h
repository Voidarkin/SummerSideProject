#pragma once

/***************************************************************************************
Title:       Enums
Author:      Joshua Griffis
Date:        2022/06/08
Description: Used to store the data on all the enums needed in the game
*****************************************************************************************/

UENUM(BlueprintType)
enum class ETargetType : uint8
{
    Self UMETA(DisplayName = "Self"),
    SingleEnemy UMETA(DisplayName = "SingleEnemy"),
    MultiEnemy UMETA(DisplayName = "MultipleEnemy"),
    SingleAlly UMETA(DisplayName = "SingleAlly"),
    MultiAlly UMETA(DisplayName = "MultipleAlly"),
    All UMETA(DisplayName = "All")
};

//Potentially delete target shape
UENUM(BlueprintType)
enum class ETargetShape : uint8
{
    All UMETA(DisplayName = "All"),
    Circle UMETA(DisplayName = "Circle"),
    Line UMETA(DisplayName = "Line"),
    Cone UMETA(DisplayName = "Cone"),
    Single UMETA(DisplayName = "Single")
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    Physical UMETA(DisplayName = "Physical"),
    Magical UMETA(DisplayName = "Magical")
};

UENUM(BlueprintType)
enum class EPhysicalType : uint8
{
    Bludgeoning UMETA(DisplayName = "Bludgeoning"),
    Piercing UMETA(DisplayName = "Piercing"),
    Slashing UMETA(DisplayName = "Slashing"),
};

UENUM(BlueprintType)
enum class EMagicType : uint8
{
    Wind UMETA(DisplayName = "Wind"),
    Water UMETA(DisplayName = "Water"),
    Fire UMETA(DisplayName = "Fire"),
    Earth UMETA(DisplayName = "Earth"),
};


UENUM(BlueprintType)
enum class EEnemyAIType : uint8
{
    Melee UMETA(DisplayName = "Melee"),
    Defensive UMETA(DisplayName = "Defensive"),
    Mage UMETA(DisplayName = "Mage"),
    Enchanter UMETA(DisplayName = "Enchanter"),
    Debuffer UMETA(DisplayName = "Debuffer"),
    Healer UMETA(DisplayName = "Healer"),
};

UENUM(BlueprintType)
enum class EUsable : uint8
{
    Battle UMETA(DisplayName = "Battle"),
    Menu UMETA(DisplayName = "Menu"),
    All UMETA(DisplayName = "All"),
    None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EAttackSpeed : uint8
{
    Slow UMETA(DisplayName = "Slow"),
    Normal UMETA(DisplayName = "Normal"),
    Fast UMETA(DisplayName = "Fast")
};


UENUM(BlueprintType)
enum class EEquipSlot : uint8
{
    Weapon UMETA(DisplayName = "Weapon"),
    Armor UMETA(DisplayName = "Armor"),
    Accessory UMETA(DisplayName = "Accessory")
};


UENUM(BlueprintType)
enum class EEffect : uint8
{
    Harm UMETA(DisplayName = "Harm"),
    Heal UMETA(DisplayName = "Heal"),
    None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EConditionTypes : uint8
{
    Poison UMETA(DisplayName = "Poison"),
    Slow UMETA(DisplayName = "Slow"),
    Paralysis UMETA(DisplayName = "Paralysis")
    //More to come
};
