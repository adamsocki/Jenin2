// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninResourceManager.h"


// Sets default values
AJeninResourceManager::AJeninResourceManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void AJeninResourceManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJeninResourceManager, ResourceAmount);
	
}
// Called when the game starts or when spawned
void AJeninResourceManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeninResourceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 AJeninResourceManager::GetResourceAmount_Implementation()
{
	// return IJenin_RTSInterface::GetResourceAmount_Implementation();

	return ResourceAmount;
}





