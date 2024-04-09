// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMainGameUIWidget.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Jenin/Player/JeninPlayerController.h"


void UJeninMainGameUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UJeninMainGameUIWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}

	if (ResourceCountText)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			if(AJeninPlayerController *JeninPlayerController = Cast<AJeninPlayerController>(GetOwningPlayer()))
			{
				if (JeninPlayerController)
				{
					ResourceCountText->TextDelegate.BindUFunction(this, "SetResourceCountField");
				}
			}
		}
	}
	return true;
}

void UJeninMainGameUIWidget::InitMainGameUIWidget()
{
	//this->ActionTiles001->


	
//	UE_LOG(LogTemp, Warning, TEXT("this init"));
	for (int i = 0; i < UnitActions.Num(); i++)
	{
		// UE_LOG(LogTemp, Warning, TEXT("this init Cnt: %d"), i);
		if (UJeninUnitAction* MyUnitAction = NewObject<UJeninUnitAction>(this, UnitActions[i]))
		{
			if (MyUnitAction != nullptr)
			{
				//UE_LOG(LogTemp, Warning, TEXT("this MyUnitAction"));
				//MyUnitActions_Test.Add(MyUnitAction);
				if (UWorld* GameWorld = GetWorld())
				{
					UE_LOG(LogTemp, Warning, TEXT("this GameWorld"));
					if (UJeninUnitActionWidget* JeninUnitActionWidget = CreateWidget<UJeninUnitActionWidget>(this, MyUnitAction->UnitActionWidget))
					{
						UE_LOG(LogTemp, Warning, TEXT("This UJeninUnitActionWidget* JeninUnitActionWidget"));
						MyUnitActionWidgets.Add(JeninUnitActionWidget);
					}
				}
			}
		}
	}
}

FText UJeninMainGameUIWidget::SetResourceCountField()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		if(AJeninPlayerController *JeninPlayerController = Cast<AJeninPlayerController>(GetOwningPlayer()))
		{
			if (Cast<IJenin_RTSInterface>(JeninPlayerController))
			{
				FString ResourceIntAsString = FString::FromInt(Execute_GetResourceAmount(JeninPlayerController));
				return FText::FromString(ResourceIntAsString);
				//ResourceCountText->SetText(ResourceCountFText);
			}
		}
	}
	return FText::FromString("NULL");
}

void UJeninMainGameUIWidget::UpdateActionTiles()
{
	// UE_LOG(LogTemp, Warning, TEXT("this UpdateAction"));
	for (int i = 0; i < MyUnitActionWidgets.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("This Actioncnt %d"), i);

		if (UJeninUnitActionWidget* MyUnitActionWidget = Cast<UJeninUnitActionWidget>(MyUnitActionWidgets[i]))
		{
			ActionTiles001->AddItem(MyUnitActionWidget);
		}
		
		// if (UJeninUnitAction* Action = Cast<UJeninUnitAction>(MyUnitActions_Test[i]))
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("This Action"));
		//
		// 	// if (UJeninUnitActionWidget* MyActionWidget = CreateWidget<UJeninUnitActionWidget>(Action->UnitActionWidget))
		// 	// {
		// 	// // //	CurrentUnitActionWidgets.Add(MyActionWidget);
		// 	// // 	//ActionTiles001->AddItem(MyActionWidget);
		// 	// //
		// 	// // 	UE_LOG(LogTemp, Warning, TEXT("This ActionWidget"));
		// 	// //
		// 	// }
		// }
		
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("This Action fail	"));
		}
	}
}
