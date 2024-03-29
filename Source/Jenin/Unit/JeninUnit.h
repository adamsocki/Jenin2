// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/Player/JeninPlayerController.h"
#include "Jenin/Resource/JeninResourceInterface.h"
#include "Jenin/UI/JeninUnitActionWidget.h"
#include "Jenin/UI/Jenin_SelectedUnitWidget.h"
#include "JeninUnit.generated.h"

UCLASS()
class JENIN_API AJeninUnit : public ACharacter, public IJenin_RTSInterface, public IJeninResourceInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AJeninUnit();

	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectionDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> UnitImage;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ResourceOverlapper;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SelectThis(); virtual void SelectThis_Implementation() override;
	virtual void DeselectThis_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void UnitMoveCommand(FVector Location);virtual void UnitMoveCommand_Implementation(FVector Location) override;
	virtual void HighlightUnit_Implementation() override;
	virtual void UnhighlightUnit_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void Collect(); virtual void Collect_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void DropOff(); virtual void DropOff_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SetIsWorkingOnResource(AJeninResourceNode* ResourceNode); virtual void SetIsWorkingOnResource_Implementation(AJeninResourceNode* ResourceNode) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SetNotWorking(); virtual void SetNotWorking_Implementation() override;

	UFUNCTION(Server, Reliable)
	void ServerMoveToLocationStarted(FVector Location);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AJeninPlayerController *UnitsJeninPlayerController;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJenin_SelectedUnitWidget> UnitWidget;
	
	UPROPERTY()
	UJenin_SelectedUnitWidget *MyUnitWidget;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UJeninUnitActionWidget>>UnitActions;
 
	UPROPERTY()
	TArray<UJeninUnitActionWidget*> MyUnitActionWidgets;
	
	UPROPERTY()
	UMaterialInterface* SelectionDecalMaterial;
	UPROPERTY()
	UMaterialInterface* HighlightedDecalMaterial;
	
	UPROPERTY(Replicated)
	int32 TeamNumber;
	UPROPERTY(Replicated)
	FLinearColor TeamColor;

	virtual int32 GetTeam_Implementation() override;

	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere)
	float ProductionTime;

	bool IsUnitWorking;

	UPROPERTY()
	AJeninResourceNode* ResourceNodeWorkingFrom;

	UPROPERTY()
	AJeninBuilding* DropOffBuilding;

	UPROPERTY()
	bool HasResource;

	UFUNCTION()
	void ResourceCollected();

	UPROPERTY()
	FTimerHandle TimerHandle;
};
