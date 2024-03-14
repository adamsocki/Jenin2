// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "JeninCameraPawn.generated.h"

UCLASS()
class JENIN_API AJeninCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJeninCameraPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;

	float ScrollSpeed = 700.0f;
	bool MoveW;
	bool MoveA;
	bool MoveS;
	bool MoveD;

	bool IsOverBottomEdge;
	bool IsOverBottomLeft;
	bool IsOverBottomRight;
	bool IsOverTopEdge;
	bool IsOverTopLeft;
	bool IsOverTopRight;
	bool IsOverLeftEdge;
	bool IsOverRightEdge;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
