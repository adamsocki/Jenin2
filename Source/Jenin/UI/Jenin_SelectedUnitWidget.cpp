// Fill out your copyright notice in the Description page of Project Settings.


#include "Jenin_SelectedUnitWidget.h"

#include "JeninMarqueeHUD.h"

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
