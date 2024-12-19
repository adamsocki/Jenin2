// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUnitActionWidget.h"

#include "JeninUnitAction.h"
// #include "JeninUnitAction.h"

FReply UJeninUnitActionWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (ParentUnitAction && MouseIsOver)
		{
			ParentUnitAction->UnitActionExecution();
			// ParentUnitAction->UnitActionDeExecution();
		}
		return FReply::Handled();
	}
	else
	{
		return FReply::Unhandled();
	}
}

void UJeninUnitActionWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	MouseIsOver = true;

	UE_LOG(LogTemp, Warning, TEXT("MouseIsOver_UnitAction"));
	if (!CursorWidget && CursorWidgetClass) // CursorWidgetClass is a reference you set in Blueprint
	{
		// Create the widget
		CursorWidget = CreateWidget<UUserWidget>(GetWorld(), CursorWidgetClass);

	//	CursorText->SetText(FText::FromString("Build"));
		// Show mouse cursor
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->SetShowMouseCursor(true);
		}
    
		// Add widget to viewport
		CursorWidget->AddToViewport();
	}

}

void UJeninUnitActionWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	MouseIsOver = false;
	if (CursorWidget)
	{
		CursorWidget->RemoveFromParent();
		CursorWidget = nullptr;
    
		// Hide cursor if needed
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			//PC->SetShowMouseCursor(false);
		}
	}
}

void UJeninUnitActionWidget::InitActions()
{
	
}

