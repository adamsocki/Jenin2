﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninBuilding.h"

#include "Components/DecalComponent.h"

// Sets default values
AJeninBuilding::AJeninBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = MyRoot;
	
	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);
	FVector DecalSize = FVector(50.0f, 100.0f, 100.0f);
	SelectionDecal->DecalSize = DecalSize;
	static ConstructorHelpers::FObjectFinder<UMaterial> SelectedMaterialAsset(TEXT("Material'/Game/App/Materials/MAT_JeninSelectionDecal.MAT_JeninSelectionDecal'")); 
	if (SelectedMaterialAsset.Succeeded())
	{
		SelectionDecal->SetDecalMaterial(SelectedMaterialAsset.Object);
		SelectionDecalMaterial = SelectedMaterialAsset.Object;
	}
	SelectionDecal->SetVisibility(false);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetReceivesDecals(false);
}

void AJeninBuilding::SelectThis_Implementation()
{
	IJenin_RTSInterface::SelectThis_Implementation();
	SelectionDecal->SetVisibility(true);
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
}

void AJeninBuilding::DeselectThis_Implementation()
{
	IJenin_RTSInterface::DeselectThis_Implementation();
	SelectionDecal->SetVisibility(false);
}

// Called when the game starts or when spawned
void AJeninBuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AJeninBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
