// Fill out your copyright notice in the Description page of Project Settings.


#include "Jenin_SelectedUnitWidget.h"

#include "JeninMarqueeHUD.h"
#include "Components/Image.h"

FReply UJenin_SelectedUnitWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
                                                          const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if(AJeninMarqueeHUD* JeninPlayerHUD = Cast<AJeninMarqueeHUD>(GetOwningPlayer()->GetHUD()))
		{
			JeninPlayerHUD->ClearSelectedUnits_Implementation();
			JeninPlayerHUD->SelectSingleUnit_Implementation(ActorReference);
		}
		return FReply::Handled();
	}
	else
	{
		return FReply::Unhandled();
	}
}

void UJenin_SelectedUnitWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (ActorReference)
	{
		AJeninUnit* JeninUnit = Cast<AJeninUnit>(ActorReference);
		JeninUnit->HighlightUnit_Implementation();

		FSlateColor Yellow = FSlateColor(FLinearColor(1.0f, 1.0f, 0.0f));
		UnitImage->SetBrushTintColor(Yellow);
	}
}

void UJenin_SelectedUnitWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	if (ActorReference)
	{
		AJeninUnit* JeninUnit = Cast<AJeninUnit>(ActorReference);
		JeninUnit->UnhighlightUnit_Implementation();

		FSlateColor White = FLinearColor::White;  // A darker yellow
		UnitImage->SetBrushTintColor(White);
	}
}