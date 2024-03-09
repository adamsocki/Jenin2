// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninSelectedUnitArea.h"
#include "GameFramework/HUD.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/Unit/JeninUnit.h"
#include "JeninMarqueeHUD.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API AJeninMarqueeHUD : public AHUD, public IJenin_RTSInterface
{
	GENERATED_BODY()

	AJeninMarqueeHUD();

public:

	virtual void BeginPlay() override;

	virtual void MarqueePressed_Implementation() override;
	virtual void MarqueeHeld_Implementation() override;
	virtual void MarqueeReleased_Implementation() override;

	virtual TArray<AJeninUnit*> GrabSelectedUnits_Implementation() override;
	virtual void AddUnitToSelectedUnitsArea_Implementation(UJenin_SelectedUnitWidget* SelectedUnitWidget) override;
	virtual void ClearSelectedUnits_Implementation() override;
	virtual void SelectSingleUnit_Implementation(AActor* Unit) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninSelectedUnitArea> UnitAreaWidget;

	UPROPERTY()
	UJeninSelectedUnitArea* MyUnitAreaWidget;	

	virtual void DrawHUD() override;
	
	bool IsDrawing;
	FVector2d StartingMousePosition;
	FVector2d CurrentMousePosition;

	FLinearColor MarqueeColor;

	UPROPERTY()
	TArray<AJeninUnit*> UnitsSelected;
	
};
