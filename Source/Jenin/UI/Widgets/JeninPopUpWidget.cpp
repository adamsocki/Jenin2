// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPopUpWidget.h"

#include "Components/Button.h"
#include "Jenin/Unit/Actions/JeninUnitAction.h"


void UJeninPopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Assuming you have a UHorizontalBox* named MyHorizontalBox;
	// Make sure to bind this variable to your actual HorizontalBox widget in the UMG Editor using the variable name.

	//this->SetVisibility(ESlateVisibility::Hidden);

	
	
	for (int i = 0; i < MyActionWidgets.Num(); i++)
	{
		
		UButton* Button = NewObject<UButton>(UButton::StaticClass());		
		UImage* ButtonImage = NewObject<UImage>(UImage::StaticClass());

		if (UJeninUnitActionWidget *JeninUnitActionWidget = Cast<UJeninUnitActionWidget>(MyActionWidgets[i]))
		{

			

			// ButtonImage->SetBrushFromTexture(JeninUnitActionWidget->UnitActionImage);
			// Button->AddChild(ButtonImage);
			// MyActionWrapBox->AddChildToWrapBox(Button);
		}
	}
	//
		// if (UJeninUnitAction* MyAction = NewObject<UJeninUnitAction>(this,Actions[i]))
		// {
		// 	MyActions.Add(MyAction);
		// 	if (UJeninUnitActionWidget* MyActionWidget = CreateWidget<UJeninUnitActionWidget>(this, MyAction->UnitActionWidget))
		// 	{
		// 		MyActionWidgets.Add(MyActionWidget);
		//
		// 		MyActionWrapBox->AddChildToWrapBox(MyActionWidget);
		//
		// 		 if (MyActionWidget->UnitActionImage)
		// 		 {
		// 		 	
		// 		// 	//ButtonImage->SetBrushF(MyActionWidget->UnitActionImage);
		// 		 }
		// 		// //
		//
		// 	}
		// }
		//
		//

	
	// for (UTexture2D* Texture : ButtonImages)
	// {
	// 	UButton* Button = NewObject<UButton>(UButton::StaticClass());
	// 	UImage* ButtonImage = NewObject<UImage>(UImage::StaticClass());
	// 	ButtonImage->SetBrushFromTexture(Texture);
	//
	// 	Button->AddChild(ButtonImage);
	// 	MyHorizontalBox->AddChildToHorizontalBox(Button);
	// }
}
