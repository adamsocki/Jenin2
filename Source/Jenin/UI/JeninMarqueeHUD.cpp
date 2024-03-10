// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMarqueeHUD.h"

#include "JeninSelectedUnitArea.h"
#include "Components/HorizontalBox.h"
#include "Jenin/Player/JeninPlayerController.h"

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

	if (UnitAreaWidget)
	{
		MyUnitAreaWidget = CreateWidget<UJeninSelectedUnitArea>(GetWorld(), UnitAreaWidget);
		MyUnitAreaWidget->AddToViewport();
	}
	
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
		GetOwningPlayerController()->GetMousePosition(CurrentMousePosition.X, CurrentMousePosition.Y);
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

	if (MyUnitAreaWidget)
	{
		MyUnitAreaWidget->UnitsBox->AddChildToHorizontalBox(SelectedUnitWidget);
	}
}

void AJeninMarqueeHUD::ClearSelectedUnits_Implementation()
{
	IJenin_RTSInterface::ClearSelectedUnits_Implementation();
	for (int i = 0; i < UnitsSelected.Num(); i++)
	{
		UnitsSelected[i]->DeselectThis_Implementation();
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
		//UE_LOG(LogTemp, Warning, TEXT("The under rect value is: %d"), UnitsUnderRectangle.Num());
		for (int i = 0; i < UnitsUnderRectangle.Num(); i++)
		{

			int32 UnitTeam = UnitsUnderRectangle[i]->GetTeam_Implementation();
			UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), UnitTeam);
			if (AJeninPlayerController *PlayerController = Cast<AJeninPlayerController>(GetOwningPlayerController()))
			{
				if (PlayerController->IsOnMyTeam_Implementation(UnitTeam))
				{
					if (IJenin_RTSInterface *SelectionInterfaceUnit = Cast<IJenin_RTSInterface>(UnitsUnderRectangle[i]))
					{
						SelectionInterfaceUnit->SelectThis_Implementation();
						UnitsSelected.AddUnique(UnitsUnderRectangle[i]);
						PlayerController->ClearSelectedBuilding_Implementation();

						
					}
				}
			}
			
			


			
		}
		UE_LOG(LogTemp, Warning, TEXT("The Selected value is: %d"), UnitsSelected.Num());

		for (int i = 0; i < UnitsSelected.Num(); i++)
		{
			if (UnitsUnderRectangle.Find(UnitsSelected[i]) == INDEX_NONE)
			{
				if (IJenin_RTSInterface *SelectionInterfaceUnit = Cast<IJenin_RTSInterface>(UnitsSelected[i]))
				{
					UnitsSelected[i]->DeselectThis_Implementation();
					UnitsSelected.RemoveAt(i);
				}
			}
		}
	}
}

