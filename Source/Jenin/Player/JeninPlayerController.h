// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Jenin/Building/JeninBuilding.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/UI/JeninSelectedUnitArea.h"

#include "JeninPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API AJeninPlayerController : public APlayerController, public IJenin_RTSInterface
{
	GENERATED_BODY()

	AJeninPlayerController();

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftMouseAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveToLocationAction = nullptr;

	UPROPERTY()
	TSubclassOf<AActor> BuildingBPClass;

	UPROPERTY()
	TSubclassOf<AActor> UnitBPClass;
	

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

	UFUNCTION(Server, Reliable)
	void ServerMoveToLocationStarted(AJeninUnit* Unit, FVector Location);

	FVector ClickedLocation;

	UPROPERTY()
	AJeninBuilding *SelectedBuilding;

	virtual void SetupPlayerStart_Implementation(AJeninPlayerStart* PlayerStart, int32 TeamNumber, FLinearColor TeamColor) override;


	virtual bool IsOnMyTeam_Implementation(int32 teamNumber) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// virtual void SetupPlayerInputComponent5(UInputComponent* PlayerInputComponent) override;
	
};
