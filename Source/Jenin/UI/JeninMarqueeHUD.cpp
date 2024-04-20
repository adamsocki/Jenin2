// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMarqueeHUD.h"

#include "JeninSelectedUnitArea.h"
#include "Components/HorizontalBox.h"
#include "Jenin/Player/JeninPlayerController.h"
#include "Widgets/JeninMainGameUIWidget.h"

AJeninMarqueeHUD::AJeninMarqueeHUD()
{
	IsDrawing = false;
	StartingMousePosition = {};
	
	
	CurrentMousePosition = {};
	MarqueeColor = FLinearColor(0.2f, 0.2f, 0.5f, 0.4f);
}

void AJeninMarqueeHUD::BeginPlay()
{
	Super::BeginPlay();

	MySelectedUnitArea = JeninUIManager->MyMainGameUIWidget->BP_SelectedUnitsArea;
	
/*
//	if (UnitAreaWidget)
// 	if (UnitAreaWidget)
// 	{
// //		MyUnitAreaWidget = CreateWidget<UJeninSelectedUnitArea>(GetWorld(), UnitAreaWidget);
// 		MyUnitAreaWidget = CreateWidget<UJeninSelectedUnitArea>(GetWorld(), UnitAreaWidget);
// 		MyUnitAreaWidget->AddToViewport();
// 	}*/
}

void AJeninMarqueeHUD::MarqueePressed_Implementation()
{
	IJenin_RTSInterface::MarqueePressed_Implementation();
	IsDrawing = true;
	if (GetOwningPlayerController())
	{
		GetOwningPlayerController()->GetMousePosition(StartingMousePosition.X, StartingMousePosition.Y);
		GetOwningPlayerController()->GetMousePosition(CurrentMousePosition.X, CurrentMousePosition.Y);
	}
	//UE_LOG(LogTemp, Log, TEXT("StartingMousePosition: %s"), *StartingMousePosition.ToString());
	//UE_LOG(LogTemp, Log, TEXT("CurrentMousePosition: %s"), *CurrentMousePosition.ToString());
	//UE_LOG(LogTemp, Log, TEXT("RectSize_X: %f, RectSize_Y: %f"), RectSize_X, RectSize_Y);
}

void AJeninMarqueeHUD::MarqueeHeld_Implementation()
{
	IJenin_RTSInterface::MarqueeHeld_Implementation();
	if (GetOwningPlayerController())
	{
		if (&CurrentMousePosition != nullptr)
		{
			GetOwningPlayerController()->GetMousePosition(CurrentMousePosition.X, CurrentMousePosition.Y);

		}
	}
}

void AJeninMarqueeHUD::MarqueeReleased_Implementation()
{
	IJenin_RTSInterface::MarqueeReleased_Implementation();
	IsDrawing = false;
}

TArray<AJeninUnit*> AJeninMarqueeHUD::GrabSelectedUnits_Implementation()
{
	return UnitsSelected;
}

void AJeninMarqueeHUD::AddUnitToSelectedUnitsArea_Implementation(UJenin_SelectedUnitWidget* SelectedUnitWidget)
{
	IJenin_RTSInterface::AddUnitToSelectedUnitsArea_Implementation(SelectedUnitWidget);

	if (MySelectedUnitArea)
	{
		// JeninUIManager->UnitAreaWidget-
		MySelectedUnitArea->UnitsBox->AddChildToWrapBox(SelectedUnitWidget);
	}
}

void AJeninMarqueeHUD::AddUnitActionsToSelectedUnitActionsArea_Implementation(
	UJeninUnitActionWidget* SelectedUnitActionWidget)
{
	IJenin_RTSInterface::AddUnitActionsToSelectedUnitActionsArea_Implementation(SelectedUnitActionWidget);

	FString &ActionID = SelectedUnitActionWidget->ActionID;
	for (const auto& Pair : JeninActionWidgetCounts)
	{
		UE_LOG(LogTemp, Warning, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}

	if (JeninActionWidgetCounts.Contains(ActionID))
	{
		if (!JeninUnitActionWidgets.Contains(SelectedUnitActionWidget))
		{
			JeninUnitActionWidgets.Add(SelectedUnitActionWidget);
			JeninActionWidgetCounts[ActionID] += 1;
		}
	}
	else
	{
		JeninActionWidgetCounts.Add(ActionID, 1);
		JeninUnitActionWidgets.Add(SelectedUnitActionWidget);
		
		if (MySelectedUnitArea)
		{
			MySelectedUnitArea->UnitActionsBox->AddChildToWrapBox(SelectedUnitActionWidget);
			// SelectedUnitActionWidget->InitActions();
			UE_LOG(LogTemp, Warning, TEXT("if (MyUnitAreaWidget)"));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("JeninActionWidgetCounts[ActionID] is: %d"), JeninActionWidgetCounts[ActionID]);
	UE_LOG(LogTemp, Warning, TEXT("JeninUnitActionWidgets.Num() is: %d"), JeninUnitActionWidgets.Num());
	/*// if (JeninActionWidgetCounts1.Contains(ActionID))
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("The ActionID name is %s"), *ActionID);
	// 	 JeninActionWidgetCounts[ActionID] += 1;
	// 	UE_LOG(LogTemp, Warning, TEXT("JeninActionWidgetCounts[ActionID] is: %d"), JeninActionWidgetCounts[ActionID]);
	// 	//for (int i = 0; i < )
	// }
	// else
	// {
	// 	//TPair<UJeninUnitActionWidget*, int32> tPair = New<TPair<UJeninUnitActionWidget*, int32>>(SelectedUnitActionWidget, 1);
	// 	JeninActionWidgetCounts.Add(ActionID, 1);
	// 	UE_LOG(LogTemp, Warning, TEXT("Not Contains(ActionID)"));
	// 	//JeninUnitActionReference.Add(SelectedUnitActionWidget,);
	// 	if (MyUnitAreaWidget)
	// 	{
	// 		MyUnitAreaWidget->UnitActionsBox->AddChildToWrapBox(SelectedUnitActionWidget);
	// 	}
	// }*/
}
void AJeninMarqueeHUD::ClearSelectedUnits_Implementation()
{
	IJenin_RTSInterface::ClearSelectedUnits_Implementation();
	for (int i = 0; i < UnitsSelected.Num(); i++)
	{
		UnitsSelected[i]->DeselectThis_Implementation();
		// @TODO NEED TO RERUN UNIT ACTION CHECK?
	}
	UnitsSelected.Empty();
}
void AJeninMarqueeHUD::SelectSingleUnit_Implementation(AActor* Unit)
{
	if (AJeninUnit* JeninUnit = Cast<AJeninUnit>(Unit))
	{
		JeninUnit->SelectThis_Implementation();
		UnitsSelected.AddUnique(JeninUnit);
	}
	IJenin_RTSInterface::SelectSingleUnit_Implementation(Unit);
}
void AJeninMarqueeHUD::RemoveUnitActionWidget_Implementation(UJeninUnitActionWidget* DeselectedUnitActionWidget)
{
	IJenin_RTSInterface::RemoveUnitActionWidget_Implementation(DeselectedUnitActionWidget);
	if (DeselectedUnitActionWidget)
	{
		JeninUnitActionWidgets.Remove(DeselectedUnitActionWidget);
		FString &ActionID = DeselectedUnitActionWidget->ActionID;
		JeninActionWidgetCounts[ActionID] -= 1;
		if (JeninActionWidgetCounts[ActionID] <= 0)
		{
			JeninActionWidgetCounts.Remove(ActionID);
		}
		UE_LOG(LogTemp, Warning, TEXT("RemoveUnitActionWidget_Implementation"));
		// UE_LOG(LogTemp, Warning, TEXT("JeninActionWidgetCounts[UnitActionWidget->ActionID] -= is: %d"), JeninActionWidgetCounts[UnitActionWidget->ActionID]);
		// if (JeninActionWidgetCounts[ActionID] >= 1)
		// {
		// 	// JeninActionWidgetCounts
		// //	JeninActionWidgetCounts.Remove(ActionID);
		// 	// DeselectedUnitActionWidget->RemoveFromParent();
		// 	//JeninUnitActionWidgets.Remove(DeselectedUnitActionWidget);
		// }
		// if (JeninActionWidgetCounts[ActionID] > 1)
		// {
		// 	JeninActionWidgetCounts[ActionID] -= 1;
		// }

		//JeninUnitActionWidgets.Remove(DeselectedUnitActionWidget);
	}
	
	

	
	// Check if the action ID exists in the count map
	// if (JeninActionWidgetCounts.Contains(UnitActionWidget->ActionID))
	// {
	// 	// Decrement the count for this action ID
	// 	JeninActionWidgetCounts[UnitActionWidget->ActionID] -= 1;
	// 	UE_LOG(LogTemp, Warning, TEXT("JeninActionWidgetCounts[UnitActionWidget->ActionID] -= is: %d"), JeninActionWidgetCounts[UnitActionWidget->ActionID]);
	//
	//
	// 	if (JeninActionWidgetCounts[UnitActionWidget->ActionID] == 0)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("JeninActionWidgetCounts[UnitActionWidget->ActionID] == 0"));
	//
	// 		JeninActionWidgetCounts.Remove(UnitActionWidget->ActionID);
	// 		UnitActionWidget->RemoveFromParent();
	// 	}
	// }
}


void AJeninMarqueeHUD::DrawHUD()
{
	Super::DrawHUD();
	
	if (IsDrawing)
	{
		float RectSize_Y = CurrentMousePosition.Y - StartingMousePosition.Y;
		float RectSize_X = CurrentMousePosition.X - StartingMousePosition.X;
	
		DrawRect(MarqueeColor,StartingMousePosition.X, StartingMousePosition.Y,  RectSize_X, RectSize_Y);
		
		TArray<AJeninUnit*> UnitsUnderRectangle;
		GetActorsInSelectionRectangle(StartingMousePosition, CurrentMousePosition, UnitsUnderRectangle, false, false);
		
		// GET THE ACTORS
		for (int i = 0; i < UnitsUnderRectangle.Num(); i++)
		{
			int32 UnitTeam = UnitsUnderRectangle[i]->GetTeam_Implementation();
			//UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), UnitTeam);
			if (AJeninPlayerController *JeninPlayerController = Cast<AJeninPlayerController>(GetOwningPlayerController()))
			{
				if (Cast<IJenin_RTSInterface>(JeninPlayerController))
				{				
					if (Execute_IsOnMyTeam(JeninPlayerController, UnitTeam))
					{
						if (Cast<IJenin_RTSInterface>(UnitsUnderRectangle[i]))
						{
							Execute_SelectThis(UnitsUnderRectangle[i]);
							UnitsSelected.AddUnique(UnitsUnderRectangle[i]);
							//JeninUnitActionWidgets.AddUnique(UnitsUnderRectangle)
							Execute_ClearSelectedBuilding(JeninPlayerController);
							UE_LOG(LogTemp, Warning, TEXT("Execute_SelectThis"));
						//	UE_LOG(LogTemp, Warning, TEXT("The Size of selected array value is: %d"), UnitsUnderRectangle[i]->UnitActions.Num());
						}
					}
				}
			}			
		}
		
		for (int i = 0; i < UnitsSelected.Num(); i++)
		{
			if (UnitsUnderRectangle.Find(UnitsSelected[i]) == INDEX_NONE)
			{
				if (Cast<IJenin_RTSInterface>(UnitsSelected[i]))
				{
					Execute_DeselectThis(UnitsSelected[i]);
					//for (int j = 0; j < UnitsSelected[i]->UnitActions.Num(); j++)
					//{
					//	Execute_RemoveUnitActionWidget(this, UnitsSelected[i]->UnitActions[j]);

					//}
					UnitsSelected.RemoveAt(i);
					//action
				}
			}
		}
	}
}
