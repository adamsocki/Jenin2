// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "JeninResourceInterface.generated.h"

class AJeninResourceNode;
class AActor;
// This class does not need to be modified.
UINTERFACE()
class UJeninResourceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JENIN_API IJeninResourceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void SetIsWorkingOnResource(AJeninResourceNode* ResourceNode);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void SetNotWorking();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void Collect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Marquee")
	void DropOff();

};
