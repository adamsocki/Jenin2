// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninGameMode.h"

#include "Jenin/Player/JeninCameraPawn.h"
#include "Jenin/Player/JeninPlayerController.h"
#include "Kismet/GameplayStatics.h"

AJeninGameMode::AJeninGameMode() 
{
	
	TSubclassOf<AActor> ActorClassToFind = AJeninPlayerStart::StaticClass(); 
	TArray<AActor*> FoundActors; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClassToFind, FoundActors);
	for (AActor* Actor : FoundActors)
	{
		PlayerStarts.Add(Cast<AJeninPlayerStart>(Actor));
	}


	TeamColor.Add(FLinearColor::Red);
	TeamColor.Add(FLinearColor::Blue);
	TeamColor.Add(FLinearColor::Green);
	TeamColor.Add(FLinearColor::Yellow);
	TeamNumber = 0;
}



void AJeninGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	if (AJeninPlayerController *JeninPlayerController = Cast<AJeninPlayerController>(NewPlayer))
	{
		UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), PlayerStarts.Num());
		if (PlayerStarts.Num() > 0) 
		{
			int32 RandomIndex = FMath::RandRange(0, PlayerStarts.Num() - 1);
			AActor* RandomPlayerStart = PlayerStarts[RandomIndex];
			if(AJeninPlayerStart* JeninPlayerStart = Cast<AJeninPlayerStart>(RandomPlayerStart))
			{
				FActorSpawnParameters SpawnCameraParameters;
				SpawnCameraParameters.Owner = this;
				AJeninCameraPawn *CameraPawn = GetWorld()->SpawnActor<AJeninCameraPawn>(SpawnCameraParameters);
				if (CameraPawn)
				{
					if (JeninPlayerStart->CameraLocation)
					{
						CameraPawn->SetActorLocation(JeninPlayerStart->CameraLocation->GetComponentLocation());
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("JeninPlayerStart->CameraLocation is invalid"));
					}
					CameraPawn->SetActorRotation(FRotator(-120.0f, 0.0f, 0.0f)); 
					JeninPlayerController->Possess(CameraPawn);
					FLinearColor IndividualTeamColor = TeamColor[TeamNumber];
					JeninPlayerController->SetupPlayerStart_Implementation(JeninPlayerStart, TeamNumber, IndividualTeamColor);
					TeamNumber++;
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("CameraPawn spawning failed"));
				}
			}
			PlayerStarts.RemoveAt(RandomIndex);
			//UE_LOG(LogTemp, Display, TEXT("Random value: %s"), *RandomValue.ToString()); // Example output, adjust based on Type
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Array is empty"));
		}
	}
	
}

void AJeninGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJeninGameMode::SetupPlayerStart_Implementation(AJeninPlayerStart* PlayerStart, int32 teamNumber, FLinearColor teamColor)
{
	IJenin_RTSInterface::SetupPlayerStart_Implementation(PlayerStart, teamNumber, teamColor);
	
	
	
}
