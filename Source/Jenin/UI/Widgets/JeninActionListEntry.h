// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserListEntry.h"
#include "Blueprint/UserWidget.h"
#include "JeninActionListEntry.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninActionListEntry : public UUserWidget, public IUserListEntry
{
	GENERATED_BODY()
};
