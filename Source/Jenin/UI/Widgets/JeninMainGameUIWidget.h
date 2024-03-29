// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "JeninMainGameUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninMainGameUIWidget : public UUserWidget, public IJenin_RTSInterface
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* ResourceCountText;

	UFUNCTION()
	FText SetResourceCountField();

	
};
