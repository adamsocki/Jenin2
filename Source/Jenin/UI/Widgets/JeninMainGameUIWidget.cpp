// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMainGameUIWidget.h"

#include "Components/TextBlock.h"

#include "Jenin/Player/JeninPlayerController.h"

#include "Jenin/Core/JeninGameMode.h"


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
