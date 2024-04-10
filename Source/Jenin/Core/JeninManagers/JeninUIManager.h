// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jenin/UI/Widgets/JeninPopUpWidget.h"
#include "Jenin/UI/Widgets/JeninMainGameUIWidget.h"
#include "JeninUIManager.generated.h"

UCLASS()
class JENIN_API AJeninUIManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJeninUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJeninPopUpWidget> BuildPopUpWidget;

	UPROPERTY()
	UJeninPopUpWidget* MyBuildPopUpWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJeninMainGameUIWidget> MainGameUIWidget;

	UPROPERTY()
	UJeninMainGameUIWidget* MyMainGameUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninSelectedUnitArea> UnitAreaWidget;
	
	
	//UPROPERTY()
	
};