// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninUnitAction.h"
#include "JeninUnitAction_Bulider.generated.h"

class UJeninBuildingSelectedWidget;
class AJeninUIManager;
class AJeninBuilding;
/**
 * 
 */
UCLASS()
class JENIN_API UJeninUnitAction_Bulider : public UJeninUnitAction
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void InitUnitAction_Builder(AJeninUIManager* UIManager);

	UPROPERTY()
	AJeninUIManager* JeninUIManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<AJeninBuilding>> JeninBuildings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AJeninBuilding*> JeninGhostBuildings;
	
	UPROPERTY()
	TArray<UJeninUnitActionWidget*> JeninGhostBuildingWidgets;

	virtual void UnitActionExecution() override;

	virtual void UnitActionMouseOver() override;
	
	virtual void InitUnitAction() override;
	
};
