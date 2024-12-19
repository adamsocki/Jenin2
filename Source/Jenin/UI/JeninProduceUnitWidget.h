// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "JeninProduceUnitWidget.generated.h"


class AJeninUnit;
class AJeninBuilding;
/**
 * 
 */
UCLASS()
class JENIN_API UJeninProduceUnitWidget : public UUserWidget
{
	GENERATED_BODY()

	


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* ProductionButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* UnitImage;
	
	UPROPERTY(EditAnywhere)
	AJeninBuilding* BuildingReference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AJeninUnit> UnitToProduce;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable) 
	void OnProductionButtonClicked();

	bool bIsUnitProductionInProgress;

	
};
