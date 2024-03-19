// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninProduceUnitWidget.h"

#include "Jenin/Player/JeninPlayerController.h"


void UJeninProduceUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ProductionButton)
	{
		//ProductionButton->OnClicked.AddDynamic(this, &UJeninProduceUnitWidget::OnProductionButtonClicked);
//ProductionButton->OnClicked
		ProductionButton->OnClicked.AddUniqueDynamic(this, &UJeninProduceUnitWidget::OnProductionButtonClicked);


	}
	bIsUnitProductionInProgress = false;
}

void UJeninProduceUnitWidget::OnProductionButtonClicked()
{
	if (bIsUnitProductionInProgress) {
		return; // Already executing, prevent additional calls
	}
	bIsUnitProductionInProgress = true; 
	if(AJeninPlayerController *JeninPlayerController = Cast<AJeninPlayerController>(GetOwningPlayer()))
	{
		if (BuildingReference)
		{
			if (JeninPlayerController->GetClass()->ImplementsInterface(UJenin_RTSInterface::StaticClass()))
			{
				IJenin_RTSInterface::Execute_ProduceUnit(JeninPlayerController, BuildingReference, UnitToProduce);
				UE_LOG(LogTemp, Warning, TEXT("This should only hit once"));
				UE_LOG(LogTemp, Warning, TEXT("This should only hit once - Instance: %p"), this);

			}
			//JeninPlayerController->ProduceUnit(BuildingReference, UnitToProduce);
		}
	}

	bIsUnitProductionInProgress = false; 

}
