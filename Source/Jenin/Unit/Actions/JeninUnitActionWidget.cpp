// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUnitActionWidget.h"
#include "JeninUnitAction.h"

FReply UJeninUnitActionWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{

		
		// if (ProductionButton)
		// {
		// 	//ProductionButton->OnClicked.AddDynamic(this, &UJeninProduceUnitWidget::OnProductionButtonClicked);
		// 	//ProductionButton->OnClicked
		// 	ProductionButton->OnClicked.AddUniqueDynamic(this, &UJeninProduceUnitWidget::OnProductionButtonClicked);
		//
		// }
		
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

	
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseEnter"));

	if (ParentUnitAction)
	{
		ParentUnitAction->UnitActionExecution();
		UE_LOG(LogTemp, Warning, TEXT("ParentUnitAction"));
	}
}

void UJeninUnitActionWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseLeave"));

}

void UJeninUnitActionWidget::InitActions()
{


	
}

