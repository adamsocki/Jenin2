// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUITileWidget.h"

void UJeninUITileWidget::NativeConstruct()
{
	Super::NativeConstruct();


	
}

bool UJeninUITileWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}



	
	return true;
}

void UJeninUITileWidget::InitUITileWidget()
{

	TotalTiles = RowCount * ColumnCount;

	
	// for (int i = 0; i < RowCount; i++)
	// {
	// 	for (int j = 0; j < ColumnCount; j++)
	// 	{
	// 		
	// 	}
	// }
	
	
}
