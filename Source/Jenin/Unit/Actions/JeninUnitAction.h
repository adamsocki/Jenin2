// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninUnitActionWidget.h"
#include "UObject/Object.h"
#include "JeninUnitAction.generated.h"

/**
 * 
 */
// UCLASS()
UCLASS(Blueprintable)
class JENIN_API UJeninUnitAction : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UJeninUnitActionWidget> UnitActionWidget;
	
	// UFUNCTION()
	virtual void UnitActionExecution();

	virtual void UnitActionMouseOver();

	virtual void InitUnitAction();
};
