// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystemInterface.h"
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
	// UEnhancedInputComponent* EnhancedInputComponent; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftMouseAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveToLocationAction = nullptr;

	bool IsLeftMouseButtonPressed;
	 
	virtual void SetupInputComponent() override;


	UFUNCTION()
	void OnLeftMouseStarted(const FInputActionValue& Value);

	UFUNCTION()
	void OnLeftMouseCompleted(const FInputActionValue& Value);

	UFUNCTION()
	void OnMoveToLocationStarted(const FInputActionValue& Value);

	FVector ClickedLocation;


	
	
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// virtual void SetupPlayerInputComponent5(UInputComponent* PlayerInputComponent) override;			
	
	




};
