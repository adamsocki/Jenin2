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



void UJeninGameInstance::HostSession(bool isLAN)
{
	DestroyExistingSession();

	if (isLAN)
	{
		IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (OnlineSubsystem) 
		{
			IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
			
			if (SessionInterface.IsValid()) 
			{
				FOnlineSessionSettings SessionSettings;
				SessionSettings.bIsLANMatch = true; 
				SessionSettings.NumPublicConnections = 4;
				SessionSettings.bShouldAdvertise = true;
				
				if (SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings))
				{
					UE_LOG(LogTemp, Warning, TEXT("HelloHelloHelloHelloHelloHelloHelloHello"));
					FName Level = "JeninMap_001";
					UGameplayStatics::OpenLevel(GetPrimaryPlayerController(),Level,true, "?listen");
				}
			}
		}
	}
	else
	{
		APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
		if (MyPlayerController)
		{
			FString Command = TEXT("Open JeninMap_001?listen");
			MyPlayerController->ConsoleCommand(Command, true); 
		}
	}

	
	
}


void UJeninGameInstance::OnFindSessionsComplete(bool wasSuccessful)
{
	if (wasSuccessful)
	{
		IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (OnlineSubsystem) 
		{
			IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
			if (SessionInterface.IsValid())
			{
				TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
				
				if (SearchResults.Num() > 0) 
				{
					const FOnlineSessionSearchResult& SearchResult = SearchResults[0];
					SessionInterface->JoinSession(0, FName("MySessionName"), SearchResult);
				}
			}
		}
	}
}

void UJeninGameInstance::JoinSession(bool isLAN)
{
	// APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
	// if (MyPlayerController)
	// {
	// 	FString Command = TEXT("Open 127.0.0.1"); // Example command
	// 	MyPlayerController->ConsoleCommand(Command, true); 
	// }
	//UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("YourConsoleCommandHere"));
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (isLAN)
	{
		APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
		if (MyPlayerController)
		{
			IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
			if (OnlineSubsystem)
			{
				IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
			
				SessionSearch->bIsLanQuery = true; 
				SessionSearch->MaxSearchResults = 1;
				

				if (SessionInterface.IsValid())
				{
					SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UJeninGameInstance::OnFindSessionsComplete); 
					SessionInterface->FindSessions(0,SessionSearch.ToSharedRef());
				}
			}
		}
	}
}



