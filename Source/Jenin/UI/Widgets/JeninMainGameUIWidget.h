﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/UI/JeninSelectedUnitArea.h"
#include "Jenin/Unit/Actions/JeninUnitAction.h"
#include "JeninMainGameUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninMainGameUIWidget : public UUserWidget, public IJenin_RTSInterface
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

public:

	UFUNCTION()
	void InitMainGameUIWidget();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* ResourceCountText;

	UFUNCTION()
	FText SetResourceCountField();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UJeninSelectedUnitArea* BP_SelectedUnitsArea;
	
	UFUNCTION()
	void UpdateActionTiles();


	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	// UScaleBox* BP_SelectedUnitsAreaScaleBox;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TArray<TSubclassOf<UJeninUnitAction>> UnitActionSlots;

	// UPROPERTY()
	// TArray<UJeninUnitAction*> MyUnitActions_Test;
	
	//
	// UPROPERTY()
	// TArray<UJeninUnitActionWidget*> MyUnitActionSlotWidgets;

	//UPROPERTY()
	// TArray<UJeninUnitActionWidget*> My

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	//class UTileView* ActionTiles001;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	//class UScaleBox* ActionTilesScaleBox;
	
	
};
