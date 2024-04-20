// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninUnitActionWidget.h"
#include "Jenin/UI/Widgets/JeninActionListEntry.h"
#include "UObject/Object.h"
#include "JeninUnitAction.generated.h"

class AJeninUIManager;
/**
 * 
 */
// UCLASS()
UENUM(BlueprintType) // Makes the enum available in the UE4 editor and Blueprints
enum class EJeninUnitActionType : uint8
{
	None UMETA(DisplayName = "None"),
	Builder UMETA(DisplayName = "Builder"),
	Rifle UMETA(DisplayName = "Rifle"),
	Shotgun UMETA(DisplayName = "Shotgun")
};

UCLASS(Blueprintable)
class JENIN_API UJeninUnitAction : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UJeninUnitActionWidget> UnitActionWidget;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UJeninActionListEntry> JeninActionListEntry;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AJeninUIManager> JeninUIManager;

	UPROPERTY(EditAnywhere)
	EJeninUnitActionType UnitActionType;
	
	// UFUNCTION()
	virtual void UnitActionExecution();

	virtual void UnitActionMouseOver();

	virtual void InitUnitAction();
	
	virtual void UnitActionDeExecution();
};
