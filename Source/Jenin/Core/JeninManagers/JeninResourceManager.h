// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "JeninResourceManager.generated.h"

UCLASS()
class JENIN_API AJeninResourceManager : public AActor, public IJenin_RTSInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJeninResourceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(Replicated)
	int32 ResourceAmount;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	int32 GetResourceAmount(); virtual int32 GetResourceAmount_Implementation() override;
	
};
