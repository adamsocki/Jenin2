// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMainMenuWidget.h"

#include "Jenin/Core/JeninGameInstance.h"


void UJeninMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UJeninMainMenuWidget::OnHostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UJeninMainMenuWidget::OnJoinButtonClicked);
	}
	
}


void UJeninMainMenuWidget::OnHostButtonClicked()
{
	// Core C++ host logic that MUST always execute
	//...
	UE_LOG(LogTemp, Warning, TEXT("Hello"));

	UJeninGameInstance *JeninGameInstance = Cast<UJeninGameInstance>(GetGameInstance());
	if (JeninGameInstance)
	{
		JeninGameInstance->HostSession(isLAN->IsChecked());
	}
	//OnHostButtonClicked_Implementation(); 
}

void UJeninMainMenuWidget::OnJoinButtonClicked()
{
	// Core C++ join logic that MUST always execute
	//...
	UJeninGameInstance *JeninGameInstance = Cast<UJeninGameInstance>(GetGameInstance());
	if (JeninGameInstance)
	{
		JeninGameInstance->JoinSession(isLAN->IsChecked());
	}

	// Call the Blueprint implementation (if any)
	//OnJoinButtonClicked_Implementation(); 
}




