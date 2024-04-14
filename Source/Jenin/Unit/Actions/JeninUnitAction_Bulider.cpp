// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUnitAction_Bulider.h"

#include "EngineUtils.h"
#include "Components/TileView.h"
#include "Jenin/Building/JeninBuilding.h"
#include "Jenin/Core/JeninManagers/JeninUIManager.h"


void UJeninUnitAction_Bulider::InitUnitAction_Builder(AJeninUIManager* UIManager)
{
	
	// JeninUIManager = UIManager;
	// // TINTIN  for Building Unit Action Builder
	// for (int i = 0; i < JeninBuildings.Num(); i++)
	// {
		
		// if (AJeninBuilding* JeninGhostBuilding = NewObject<AJeninBuilding>(this, JeninBuildings[i]))
		// {
		// 	
		// 	JeninGhostBuildings.Add(JeninGhostBuilding);
		// 	// if (UJeninBuildingSelectedWidget* JeninGhostBuildingWidget = Cast<UJeninBuildingSelectedWidget>(JeninGhostBuilding->BuildingWidget))
		// 	// {
		// 	//
		//
		// }


			
			// }
		//if (U)
		// // TINTIN  Unit Action Widgets
		// if (UJeninUnitActionWidget* MyJeninUnitActionWidget_Building = CreateWidget<UJeninUnitActionWidget>(JeninBuildings[i]))


		
	
}

void UJeninUnitAction_Bulider::UnitActionExecution()
{
	Super::UnitActionExecution();
	
	// @TODO: Update UI Tile Unit Action with all the AJeninBuildings in this Unit Action
	if (JeninUIManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitActionExecution JeninUIManager"));
		if (JeninUIManager->MyMainGameUIWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("UnitActionExecution MyMainGameUIWidget"));
			if (JeninUIManager->MyMainGameUIWidget->ActionTiles001)
			{
				UE_LOG(LogTemp, Warning, TEXT("UnitActionExecution ActionTiles001"));
				JeninUIManager->MyMainGameUIWidget->ActionTiles001->ClearListItems();

				for (int i = 0; i < JeninGhostBuildingWidgets.Num(); i++)
				{
					UE_LOG(LogTemp, Warning, TEXT("UnitActionExecution JeninGhostBuildingWidgets A %d"), i);
					if (UJeninUnitActionWidget* MyUnitActionWidget = Cast<UJeninUnitActionWidget>(JeninGhostBuildingWidgets[i]))
					{
						// MyUnitActionWidget->UnitActionImage =
						//MyUnitActionWidget->UnitActionImage = JeninGhostBuildingWidgets[i]->
						UE_LOG(LogTemp, Warning, TEXT("UnitActionExecution JeninGhostBuildingWidgets B Actioncnt %d"), i);
						UE_LOG(LogTemp, Warning, TEXT("UnitActionExecution JeninGhostBuildingWidgets"));
						JeninUIManager->MyMainGameUIWidget->ActionTiles001->SetVisibility(ESlateVisibility::Visible);
						JeninUIManager->MyMainGameUIWidget->ActionTiles001->AddItem(MyUnitActionWidget);
						// MyUnitActionWidget->UnitActionImage
					}
					//JeninUIManager->MyMainGameUIWidget->ActionTiles001->AddItem
				}
			}
		}
	}
}

void UJeninUnitAction_Bulider::UnitActionMouseOver()
{
	Super::UnitActionMouseOver();

	
}

void UJeninUnitAction_Bulider::InitUnitAction()
{
	Super::InitUnitAction();
	UE_LOG(LogTemp, Warning, TEXT("TINTIN  InitUnitAction InitUnitAction"));

	for (TActorIterator<AJeninUIManager> It(GetWorld()); It; ++It)
	{

		if (AJeninUIManager* UIManager = *It)
		{
			UE_LOG(LogTemp, Warning, TEXT("TINTIN  UIManager Found"));

			JeninUIManager = UIManager;

			for (int i = 0; i < JeninBuildings.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("TINTIN  JeninBuildings A %d"), i);

				UE_LOG(LogTemp, Warning, TEXT("TINTIN  JeninBuildings"));


				UE_LOG(LogTemp, Warning, TEXT("TINTIN  JeninGhostBuilding"));


				if (JeninBuildings[i].IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("TINTIN  JeninBuildings[i].IsValid("));
				
					if (AJeninBuilding* LoadedGhostBuilding = JeninBuildings[i].LoadSynchronous())
					{
						UE_LOG(LogTemp, Warning, TEXT("TINTIN  LoadedGhostBuilding"));
				
						JeninGhostBuildings.Add(LoadedGhostBuilding);
						if (LoadedGhostBuilding->MyBuilding_UnitActionWidget)
						{
							UE_LOG(LogTemp, Warning, TEXT("TINTIN  LoadedGhostBuilding->MyBuilding_UnitActionWidget"));
				
							UE_LOG(LogTemp, Warning, TEXT("TINTIN  MyBuilding_UnitActionWidget"));
							JeninGhostBuildingWidgets.Add(LoadedGhostBuilding->MyBuilding_UnitActionWidget);
							if (LoadedGhostBuilding->BuildingImage)
							{
								LoadedGhostBuilding->MyBuilding_UnitActionWidget->UnitActionImage->SetBrushFromTexture(LoadedGhostBuilding->BuildingImage);

							}
						}
					}
				
					
				
				}
				// if (UJeninUnitActionWidget* JeninGhostBuilding_ActionWidget = CreateWidget<UJeninUnitActionWidget>(this, JeninGhostBuilding->Building_UnitActionWidget))
				// {
				// 	
				// 	UE_LOG(LogTemp, Warning, TEXT("TINTIN  UJeninBuildingSelectedWidget"));
				//
				// 	JeninGhostBuildingWidgets.Add(JeninGhostBuilding_ActionWidget);
				// }

				
				// if (AJeninBuilding* JeninGhostBuilding = NewObject<AJeninBuilding>(this, JeninBuildings[i]))
				// {
				// 	
				// }
			}
			
		}

		// Do something with the Actor
	} 

	// TINTIN  for Building Unit Action Builder
	


			
	// }
	//if (U)
	// // TINTIN  Unit Action Widgets
	// if (UJeninUnitActionWidget* MyJeninUnitActionWidget_Building = CreateWidget<UJeninUnitActionWidget>(JeninBuildings[i]))
}



