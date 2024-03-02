// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "TestControl.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API ATestControl : public APlayerController
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
};
