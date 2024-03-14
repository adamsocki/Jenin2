﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Jenin/Building/JeninBuilding.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/UI/JeninEdgeScroll.h"

#include "JeninPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API AJeninPlayerController : public APlayerController, public IJenin_RTSInterface
{
	GENERATED_BODY()

	AJeninPlayerController();

	//@TODO -> allow mouse pivot camera
	//@TODO -> mouse wheel scroll camera
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftMouseAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveToLocationAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MouseScrollWheelAction = nullptr;

	UPROPERTY()
	TSubclassOf<AActor> BuildingBPClass;

	UPROPERTY()
	TSubclassOf<AActor> UnitBPClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninEdgeScroll> EdgeScrollWidget;

	UPROPERTY()
	UJeninEdgeScroll* MyEdgeScrollWidget;	

	bool IsLeftMouseButtonPressed;
	 
	virtual void SetupInputComponent() override;
	virtual void ClearSelectedBuilding_Implementation() override;
	
	UPROPERTY(Replicated)
	int32 TeamNumber;
	UPROPERTY(Replicated)
	FLinearColor TeamColor;


	UFUNCTION()
	void OnLeftMouseStarted(const FInputActionValue& Value);

	UFUNCTION()
	void OnLeftMouseCompleted(const FInputActionValue& Value);

	UFUNCTION()
	void OnMoveToLocationStarted(const FInputActionValue& Value);

	UFUNCTION()
	void OnMouseScrollWheel(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ServerMoveToLocationStarted(AJeninUnit* Unit, FVector Location);

	FVector ClickedLocation;

	UPROPERTY(EditAnywhere)
	float MouseZoomSpeed;

	UPROPERTY()
	AJeninBuilding *SelectedBuilding;

	virtual void SetupPlayerStart_Implementation(AJeninPlayerStart* PlayerStart, int32 TeamNumber, FLinearColor TeamColor) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void ProduceUnit(AJeninBuilding* BuildingReference, TSubclassOf<AJeninUnit> UnitToProduce); virtual void ProduceUnit_Implementation(AJeninBuilding* BuildingReference, TSubclassOf<AJeninUnit> UnitToProduce) override;

	UFUNCTION(Server, Reliable)
	void ServerProduceUnit(AJeninBuilding* BuildingReference, TSubclassOf<AJeninUnit> UnitToProduce);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	bool IsOnMyTeam(int32 a); virtual bool IsOnMyTeam_Implementation(int32 teamNumber) override;

	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// virtual void SetupPlayerInputComponent5(UInputComponent* PlayerInputComponent) override;


};
