// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/Resource/JeninResourceInterface.h"
#include "Jenin/UI/JeninBuildingSelectedWidget.h"
#include "Jenin/UI/JeninProduceUnitWidget.h"
#include "JeninBuilding.generated.h"

UCLASS()
class JENIN_API AJeninBuilding : public AActor, public IJenin_RTSInterface, public IJeninResourceInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJeninBuilding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Building", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> BuildingImage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDecalComponent* SelectionDecal;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* UnitSpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Building", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY()
	UMaterialInterface* SelectionDecalMaterial;

	
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SelectThis(); virtual void SelectThis_Implementation() override;

	virtual void DeselectThis_Implementation() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(Replicated)
	int32 TeamNumber;
	UPROPERTY(Replicated)
	FLinearColor TeamColor;

	virtual int32 GetTeam_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Building", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninBuildingSelectedWidget> BuildingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Building", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ProductionWidget;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Building", meta = (AllowPrivateAccess = "true"))
	// TArray<UJeninProduceUnitWidget*> ActionBoxButtonWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Building", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AJeninUnit>> SpawnableUnits;
	
	UFUNCTION()
	void AddUnitToQueue(TSubclassOf<AJeninUnit> NewUnit);
	
	UPROPERTY(Replicated)
	TArray<TSubclassOf<AJeninUnit>> UnitProductionQueue;

	UPROPERTY()
	TSubclassOf<AJeninUnit> UnitToProduce;
	
	UPROPERTY()
	UJeninBuildingSelectedWidget *MyBuildingSelectedWidget;

	UPROPERTY(EditAnywhere)
	FText BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Building", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninUnitActionWidget> Building_UnitActionWidget;
	
	UPROPERTY()
	UJeninUnitActionWidget* MyBuilding_UnitActionWidget;
	
	bool IsProducingUnit;
	
	UFUNCTION()
	void ProcessProductionQueue();

	UPROPERTY(EditAnywhere)
	float ProductionUnitTimerGranularity;

	float ProductionTimeNeeded;
	
	float ProductionTimeSpent;
	
	UPROPERTY(Replicated)
	float ProductionProgress;

	bool NeedToUpdateUI;
	
	//UFUNCTION()
	void UpdateUI();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
