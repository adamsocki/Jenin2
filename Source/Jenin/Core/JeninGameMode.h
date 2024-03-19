// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jenin_RTSInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Jenin/Player/JeninPlayerStart.h"
#include "JeninGameMode.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API AJeninGameMode : public AGameModeBase, public IJenin_RTSInterface
{
	GENERATED_BODY()
	
	AJeninGameMode();

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual void BeginPlay() override;
public:
	void OnLevelLoaded(AActor* LoadedActor, ULevel* LoadedLevel);
	UPROPERTY()
	TArray<AJeninPlayerStart*> PlayerStarts;
	
	int32 TeamNumber;
	TArray<FLinearColor> TeamColor;

	virtual void SetupPlayerStart_Implementation(AJeninPlayerStart* PlayerStart, int32 teamNumber, FLinearColor teamColor) override;
};
