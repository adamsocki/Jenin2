// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUnitActionWidget.h"
#include "JeninUnitAction.h"

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
}

void UJeninUnitActionWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	MouseIsOver = false;
}

void UJeninUnitActionWidget::InitActions()
{
	
}

