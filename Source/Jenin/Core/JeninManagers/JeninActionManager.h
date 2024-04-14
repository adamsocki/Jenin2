// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JeninActionManager.generated.h"

UCLASS()
class JENIN_API AJeninActionManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJeninActionManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	




	
};
