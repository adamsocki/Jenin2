﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "JeninUnitActionWidget.generated.h"


class UJeninUnitAction;

/**
 *
 *
 * 
 */

UCLASS()
class JENIN_API UJeninUnitActionWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* UnitActionImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionID;

	UPROPERTY()
	UJeninUnitAction *ParentUnitAction;

	
	bool MouseIsOver = false;

	UFUNCTION()
	void InitActions();

	UPROPERTY()
	UUserWidget* CursorWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Jenin")
	TSubclassOf<UUserWidget> CursorWidgetClass;

	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* CursorText = nullptr;

};
