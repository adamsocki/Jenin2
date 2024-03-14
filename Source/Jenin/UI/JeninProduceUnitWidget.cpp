// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninProduceUnitWidget.h"

#include "Jenin/Player/JeninPlayerController.h"


void UJeninProduceUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ProductionButton)
	{
		ProductionButton->OnClicked.AddDynamic(this, &UJeninProduceUnitWidget::OnProductionButtonClicked);
	}

	
}



void UJeninProduceUnitWidget::OnProductionButtonClicked()
{
	if(AJeninPlayerController *JeninPlayerController = Cast<AJeninPlayerController>(GetOwningPlayer()))
	{
		if (BuildingReference)
		{
			if (JeninPlayerController->GetClass()->ImplementsInterface(UJenin_RTSInterface::StaticClass()))
			{
				IJenin_RTSInterface::Execute_ProduceUnit(JeninPlayerController, BuildingReference, UnitToProduce);
			}
			//JeninPlayerController->ProduceUnit(BuildingReference, UnitToProduce);
		}
	}
}
