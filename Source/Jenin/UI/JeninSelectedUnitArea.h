// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JeninSelectedUnitArea.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninSelectedUnitArea : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UWrapBox* UnitsBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UWrapBox* UnitActionsBox;

};
