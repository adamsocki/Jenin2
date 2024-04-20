// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninSelectedUnitArea.h"
#include "GameFramework/HUD.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/Core/JeninManagers/JeninUIManager.h"
#include "Jenin/Unit/JeninUnit.h"
#include "Widgets/JeninMainGameUIWidget.h"
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

	// *************** // 
	//     MANAGERS	   //
	// *************** //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Managers")
	TSoftObjectPtr <AJeninUIManager> JeninUIManager;

	virtual void BeginPlay() override;

	virtual void MarqueePressed_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void MarqueeHeld(); virtual void MarqueeHeld_Implementation() override;
	virtual void MarqueeReleased_Implementation() override;

	virtual TArray<AJeninUnit*> GrabSelectedUnits_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void AddUnitToSelectedUnitsArea(UJenin_SelectedUnitWidget* SelectedUnitWidget);virtual void AddUnitToSelectedUnitsArea_Implementation(UJenin_SelectedUnitWidget* SelectedUnitWidget) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void AddUnitActionsToSelectedUnitActionsArea(UJeninUnitActionWidget* SelectedUnitActionWidget);virtual void AddUnitActionsToSelectedUnitActionsArea_Implementation(UJeninUnitActionWidget* SelectedUnitActionWidget) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void ClearSelectedUnits(); virtual void ClearSelectedUnits_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SelectSingleUnit(AActor* Unit); virtual void SelectSingleUnit_Implementation(AActor* Unit) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void RemoveUnitActionWidget(UJeninUnitActionWidget* DeselectedUnitActionWidget); virtual void RemoveUnitActionWidget_Implementation(UJeninUnitActionWidget* DeselectedUnitActionWidget) override;


	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninSelectedUnitArea> UnitAreaWidget;
	UPROPERTY()
	UJeninSelectedUnitArea* MySelectedUnitArea;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninMainGameUIWidget> JeninMainGameUIWidget;
	UPROPERTY()
	UJeninMainGameUIWidget* MyJeninMainGameUIWidget;


	
	// UPROPERTY()
	// UJeninSelectedUnitArea* MyUnitAreaWidget;
	
	UPROPERTY()
	TSet<TSubclassOf<UJeninUnitActionWidget>> JeninUnitActionWidgetClasses;

	UPROPERTY()
	TArray<UJeninUnitActionWidget*> JeninUnitActionWidgets;

	
	virtual void DrawHUD() override;
	
	bool IsDrawing;
	FVector2d StartingMousePosition;
	FVector2d CurrentMousePosition;

	FLinearColor MarqueeColor;

	UPROPERTY()
	TArray<AJeninUnit*> UnitsSelected;

	TMap<FString, TPair<UTexture2D*, int32>> ActionCounts;

	//UPROPERTY()
	TMap<FString, int32> JeninActionWidgetCounts;
	TMap<FString, TPair<UJeninUnitActionWidget*, int32>> JeninActionWidgetCounts1;
	//TMap<FString, UJeninUnitActionWidget> JeninUnitActionReference;
	TMap<FString, TArray<UJeninUnitActionWidget*>> JeninActionWidgetArrays333;
	
};
