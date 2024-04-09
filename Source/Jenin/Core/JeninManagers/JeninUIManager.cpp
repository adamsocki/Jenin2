// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUIManager.h"

//	#include "Runtime/TraceLog/standalone_epilogue.h"


// Sets default values
AJeninUIManager::AJeninUIManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJeninUIManager::BeginPlay()
{
	Super::BeginPlay();

	if (BuildPopUpWidget)
	{
		MyBuildPopUpWidget = CreateWidget<UJeninPopUpWidget>(GetWorld(), BuildPopUpWidget);
	}

	if (MainGameUIWidget)
	{
		MyMainGameUIWidget = CreateWidget<UJeninMainGameUIWidget>(GetWorld(), MainGameUIWidget);
		MyMainGameUIWidget->AddToViewport();
		MyMainGameUIWidget->InitMainGameUIWidget();
		MyMainGameUIWidget->UpdateActionTiles();
	}


	
}

// Called every frame
void AJeninUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

