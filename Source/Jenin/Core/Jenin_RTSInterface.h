// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Jenin/Unit/JeninUnit.h"
#include "Jenin/UI/Jenin_SelectedUnitWidget.h"
#include "UObject/Interface.h"
#include "Jenin_RTSInterface.generated.h"

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
	void ClearSelectedUnits();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void SelectSingleUnit(AActor* Unit);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void HighlightUnit();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void UnhighlightUnit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void ClearSelectedBuilding();
};
