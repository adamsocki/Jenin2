// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JeninUITileWidget.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninUITileWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual bool Initialize() override;

public:

	UFUNCTION()
	void InitUITileWidget();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTileView* JeninTileView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UScaleBox* JeninScaleBox;

	UPROPERTY(EditAnywhere)
	int32 RowCount;

	UPROPERTY(EditAnywhere)
	int32 ColumnCount;
	
	int32 TotalTiles;
};
