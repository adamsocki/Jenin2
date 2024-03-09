// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JeninGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Session")
	void HostSession();   

	UFUNCTION(BlueprintCallable, Category = "Session")
	void JoinSession();  

};
