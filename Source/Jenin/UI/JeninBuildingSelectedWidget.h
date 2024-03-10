// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

};
