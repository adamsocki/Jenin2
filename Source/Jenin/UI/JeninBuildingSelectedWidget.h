// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "JeninBuildingSelectedWidget.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninBuildingSelectedWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	AActor* ActorReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UWrapBox* ActionBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* BuildingNameText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* BuildingImage;

	//virtual void NativeConstruct() override;
};
