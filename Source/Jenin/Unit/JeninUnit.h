// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/UI/Jenin_SelectedUnitWidget.h"
#include "JeninUnit.generated.h"

UCLASS()
class JENIN_API AJeninUnit : public ACharacter, public IJenin_RTSInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AJeninUnit();

	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectionDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> UnitImage;

	virtual void SelectThis_Implementation() override;
	virtual void DeselectThis_Implementation() override;
	virtual void UnitMoveCommand_Implementation(FVector Location) override;
	virtual void HighlightUnit_Implementation() override;
	virtual void UnhighlightUnit_Implementation() override;

	UFUNCTION(Server, Reliable)
	void ServerMoveToLocationStarted(FVector Location);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJenin_SelectedUnitWidget> UnitWidget;
	
	UPROPERTY()
	UJenin_SelectedUnitWidget *MyUnitWidget;

	UPROPERTY()
	UMaterialInterface* SelectionDecalMaterial;
	UPROPERTY()
	UMaterialInterface* HighlightedDecalMaterial;

	
	
};
