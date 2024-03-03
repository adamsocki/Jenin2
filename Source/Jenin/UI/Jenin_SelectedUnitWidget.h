// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Jenin_SelectedUnitWidget.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJenin_SelectedUnitWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	AActor* ActorReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* UnitImage;
};
