// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPlayerStart.h"


// Sets default values
AJeninPlayerStart::AJeninPlayerStart()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = MyRoot;
	
	CameraLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraLocation"));
	CameraLocation->SetupAttachment(RootComponent);

	BuildingLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingLocation"));
	BuildingLocation->SetupAttachment(RootComponent);
	Unit_001 = CreateDefaultSubobject<UBoxComponent>(TEXT("Unit_001"));
	Unit_001->SetupAttachment(RootComponent);
	Unit_002 = CreateDefaultSubobject<UBoxComponent>(TEXT("Unit_002"));
	Unit_002->SetupAttachment(RootComponent);
	Unit_003 = CreateDefaultSubobject<UBoxComponent>(TEXT("Unit_003"));
	Unit_003->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AJeninPlayerStart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeninPlayerStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

