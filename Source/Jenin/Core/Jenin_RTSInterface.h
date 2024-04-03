// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jenin/Player/JeninPlayerStart.h"
#include "Jenin/UI/Jenin_SelectedUnitWidget.h"
#include "Jenin/Unit/Actions/JeninUnitActionWidget.h"
#include "UObject/Interface.h"
#include "Jenin_RTSInterface.generated.h"

class AJeninBuilding;
class AJeninUnit;
// This class does not need to be modified.
UINTERFACE()
class UJenin_RTSInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JENIN_API IJenin_RTSInterface
{
	GENERATED_BODY()

	//IJenin_RTSInterface();

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void MarqueePressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void MarqueeHeld();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void MarqueeReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void SelectThis();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void DeselectThis();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void UnitMoveCommand(FVector Location);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	TArray<AJeninUnit*> GrabSelectedUnits();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void AddUnitToSelectedUnitsArea(UJenin_SelectedUnitWidget* SelectedUnitWidget);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void AddUnitActionsToSelectedUnitActionsArea(UJeninUnitActionWidget* SelectedUnitActionWidget);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void ClearSelectedUnits();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void SelectSingleUnit(AActor* Unit);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void HighlightUnit();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void UnhighlightUnit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void ClearSelectedBuilding();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "PlayerStart")
	void SetupPlayerStart(AJeninPlayerStart* PlayerStart, int32 TeamNumber, FLinearColor TeamColor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	int32 GetTeam();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	bool IsOnMyTeam(int32 TeamNumber);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void ProduceUnit(AJeninBuilding *BuildingReference, TSubclassOf<AJeninUnit> UnitToProduce);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	int32 GetResourceAmount();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void IncrementResourceAmount(int32 Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void RemoveUnitActionWidget(UJeninUnitActionWidget* DeselectedUnitActionWidget);
	
};
