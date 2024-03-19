#pragma once

UENUM(BlueprintType)
enum class EJeninUnitType
{
	Weapon     UMETA(DisplayName = "Weapon"),
	Consumable UMETA(DisplayName = "Consumable"),
	Armor      UMETA(DisplayName = "Armor")
};
