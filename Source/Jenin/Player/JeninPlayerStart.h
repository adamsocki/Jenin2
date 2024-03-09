// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "JeninPlayerStart.generated.h"

UCLASS()
class JENIN_API AJeninPlayerStart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJeninPlayerStart();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* CameraLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BuildingLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* Unit_001;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* Unit_002;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* Unit_003;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere);
	int32 UnitInitCount;
	UPROPERTY(EditAnywhere);
	int32 BuildingInitCount;
};
