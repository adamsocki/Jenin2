// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "JeninBuilding.generated.h"

UCLASS()
class JENIN_API AJeninBuilding : public AActor, public IJenin_RTSInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJeninBuilding();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDecalComponent* SelectionDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	UMaterialInterface* SelectionDecalMaterial;

	virtual void SelectThis_Implementation() override;
	virtual void DeselectThis_Implementation() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
