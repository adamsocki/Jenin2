// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "Jenin/Building/JeninBuilding.h"

#include "Jenin/Unit/Actions/JeninUnitAction.h"
#include "Jenin/Unit/Actions/JeninUnitActionWidget.h"
#include "JeninPopUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninPopUpWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	
	UPROPERTY(meta = (BindWidget))
	UWrapBox* MyActionWrapBox = nullptr;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UJeninUnitAction>> Actions;

	UPROPERTY()
	TArray<UJeninUnitAction*> MyActions;

	UPROPERTY()
	TArray<UJeninUnitActionWidget*> MyActionWidgets;

	UPROPERTY()
	TArray<TSubclassOf<AJeninBuilding>> JeninBuildings;

	

};
