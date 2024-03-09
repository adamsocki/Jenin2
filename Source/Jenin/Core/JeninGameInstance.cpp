// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninGameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

void DestroyExistingSession()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem) 
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) 
		{
			FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
			if (ExistingSession) 
			{
				SessionInterface->DestroySession(NAME_GameSession);
			}
		}
	}
}



void UJeninGameInstance::HostSession()
{
	DestroyExistingSession();
	
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem) 
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		
		if (SessionInterface.IsValid()) 
		{
			FOnlineSessionSettings SessionSettings;
			// ... (configure your session settings)
			SessionSettings.bIsLANMatch = false;  // Example: Set to true for LAN
			SessionSettings.NumPublicConnections = 4; // Example: Max players
			SessionSettings.bShouldAdvertise = true;
			//SessionSettings.
			if (SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings))
			{
				UE_LOG(LogTemp, Warning, TEXT("HelloHelloHelloHelloHelloHelloHelloHello"));
				FName Level = "JeninMap_001";
				UGameplayStatics::OpenLevel(GetPrimaryPlayerController(),Level,false, "?listen");
			}
			
			
		}
	}
}

void UJeninGameInstance::JoinSession()
{
	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
	if (MyPlayerController)
	{
		FString Command = TEXT("Open 127.0.0.1"); // Example command
		MyPlayerController->ConsoleCommand(Command, true); 
	}
	//UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("YourConsoleCommandHere")); 
}


