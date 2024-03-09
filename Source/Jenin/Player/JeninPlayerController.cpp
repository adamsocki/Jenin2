// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninPlayerController.h"

#include "AIController.h"
#include "Net/UnrealNetwork.h"
#include "DetourCrowdAIController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/HorizontalBox.h"
#include "Jenin/Building/JeninBuilding.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/UI/JeninMarqueeHUD.h"

AJeninPlayerController::AJeninPlayerController()
{
	ClickedLocation = {};
	IsLeftMouseButtonPressed = {};

	static ConstructorHelpers::FClassFinder<AActor> BPFinderBuilding(TEXT("Blueprint'/Game/App/Buildings/BP_JeninBuilding_Type001.BP_JeninBuilding_Type001_C'"));
	if (BPFinderBuilding.Class != nullptr)
	{
		BuildingBPClass = BPFinderBuilding.Class; 
	}

	static ConstructorHelpers::FClassFinder<AActor> BPFinderUnit(TEXT("Blueprint'/Game/App/Units/BP_JeninUnit_001.BP_JeninUnit_001_C'"));
	if (BPFinderUnit.Class != nullptr)
	{
		UnitBPClass = BPFinderUnit.Class; 
	}
}
void AJeninPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJeninPlayerController, TeamNumber);
	DOREPLIFETIME(AJeninPlayerController, TeamColor);
}

void AJeninPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnLeftMouseStarted);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Completed, this, &AJeninPlayerController::OnLeftMouseCompleted);
		EnhancedInputComponent->BindAction(MoveToLocationAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnMoveToLocationStarted);
	}
}

void AJeninPlayerController::ClearSelectedBuilding_Implementation()
{
	IJenin_RTSInterface::ClearSelectedBuilding_Implementation();
	if(SelectedBuilding)
	{
		SelectedBuilding->DeselectThis_Implementation();
		SelectedBuilding = nullptr;
	}
}

void AJeninPlayerController::ServerMoveToLocationStarted_Implementation(AJeninUnit* Unit, FVector Location)
{
	
	//Unit->UnitMoveCommand_Implementation(Location);

	if (AAIController *UnitAIController = Unit->GetController<AAIController>())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitMov AIController Unit."));
		//UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand_Implementation called. Location: %s"), *Location.ToString());
		if (HasAuthority()) // or Role == ROLE_Authority
		{
			UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand executing on SERVER for %s"), *GetName());
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand executing on CLIENT for %s"), *GetName());
		}
		UnitAIController->StopMovement();
		UnitAIController->MoveToLocation(Location);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI CONTROLLER FOR UNIT."));

	}
	UE_LOG(LogTemp, Warning, TEXT("ServerUpdate for move."));
}


void AJeninPlayerController::SetupPlayerStart_Implementation(AJeninPlayerStart* PlayerStart, int32 teamNumber, FLinearColor teamColor)
{
	IJenin_RTSInterface::SetupPlayerStart_Implementation(PlayerStart, teamNumber, teamColor);
	if (HasAuthority())
	{
		TeamNumber = teamNumber;
		TeamColor = teamColor;
		UE_LOG(LogTemp, Warning, TEXT("ControllerSetupSPAWN"));

		FActorSpawnParameters SpawnBuildingParameters;
		//SpawnBuildingParameters.Owner = this;
		FRotator SpawnRotation = {};
		AJeninBuilding* SpawnedBuilding = GetWorld()->SpawnActor<AJeninBuilding>(BuildingBPClass, PlayerStart->BuildingLocation->GetComponentLocation(), SpawnRotation);
		SpawnedBuilding->TeamNumber = TeamNumber;
		SpawnedBuilding->TeamColor = TeamColor;
		
		FActorSpawnParameters SpawnUnit001Parameters;
		SpawnUnit001Parameters.Owner = this;
		AJeninUnit* SpawnedUnit001 = GetWorld()->SpawnActor<AJeninUnit>(UnitBPClass, PlayerStart->Unit_001->GetComponentLocation(), SpawnRotation);
		SpawnedUnit001->TeamNumber = TeamNumber;
		SpawnedUnit001->TeamColor = TeamColor;
	
		FActorSpawnParameters SpawnUnit002Parameters;
		//SpawnUnit002Parameters.Owner = this;
		AJeninUnit* SpawnedUnit002 = GetWorld()->SpawnActor<AJeninUnit>(UnitBPClass, PlayerStart->Unit_002->GetComponentLocation(), SpawnRotation);
		SpawnedUnit002->TeamNumber = TeamNumber;
		SpawnedUnit002->TeamColor = TeamColor;
	
		FActorSpawnParameters SpawnUnit003Parameters;
		//SpawnUnit003Parameters.Owner = this;
		AJeninUnit* SpawnedUnit003 = GetWorld()->SpawnActor<AJeninUnit>(UnitBPClass, PlayerStart->Unit_003->GetComponentLocation(), SpawnRotation);
		SpawnedUnit003->TeamNumber = TeamNumber;
		SpawnedUnit003->TeamColor = TeamColor;
	
	}
	
}

bool AJeninPlayerController::IsOnMyTeam_Implementation(int32 teamNumber)
{
	
	if (TeamNumber == teamNumber)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void AJeninPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalController())
	{
		this->bShowMouseCursor = true;
		this->bEnableClickEvents = true;
		this->bEnableMouseOverEvents = true;
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		this->SetInputMode(InputMode);
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AJeninPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsLeftMouseButtonPressed)
	{
		ClearSelectedBuilding_Implementation();
		AJeninMarqueeHUD* JeninHUD = Cast<AJeninMarqueeHUD>(GetHUD());
		if (JeninHUD)
		{
			FHitResult HitResult;
			bool HitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
			if (HitSuccessful && JeninHUD->UnitsSelected.Num() == 0)
			{
				if (HitResult.GetActor()->IsA(AJeninBuilding::StaticClass()))
				{
					UE_LOG(LogTemp, Warning, TEXT("HitBuilding"));
					SelectedBuilding = Cast<AJeninBuilding>(HitResult.GetActor());
					

					int32 BuildingTeam = SelectedBuilding->GetTeam_Implementation();
					if (this->IsOnMyTeam_Implementation(BuildingTeam))
					{
						SelectedBuilding->SelectThis_Implementation();
						UE_LOG(LogTemp, Warning, TEXT("SelectThisSholundwixk"));

					}
					
					
				}
			}
			AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
			if (MarqueeHUD) 
			{
				IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD);
				if (JeninInterface)
				{
					JeninInterface->MarqueeHeld_Implementation();
				}   
			} 
		}
		
	}
}

void AJeninPlayerController::OnLeftMouseStarted(const FInputActionValue& Value)
{
	IsLeftMouseButtonPressed = true;
	AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
	if (MarqueeHUD) 
	{
		IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD);
		if (JeninInterface)
		{
			JeninInterface->MarqueePressed_Implementation();
		}   
	} 
}

void AJeninPlayerController::OnLeftMouseCompleted(const FInputActionValue& Value)
{
	IsLeftMouseButtonPressed = false;
	AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
	if (MarqueeHUD) 
	{
		IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD); 
		if (JeninInterface)
		{
			JeninInterface->MarqueeReleased_Implementation();  
		}   
	} 
}

void AJeninPlayerController::OnMoveToLocationStarted(const FInputActionValue& Value)
{
	FHitResult Hit;
	bool HitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (HitSuccessful)
	{
		AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
		if (MarqueeHUD)
		{
			IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD);
			if (JeninInterface)
			{
				TArray<AJeninUnit*> units = JeninInterface->GrabSelectedUnits_Implementation();
				if (units.Num() > 0)
				{
					UE_LOG(LogTemp, Display, TEXT("Move command initiated for %d selected units. Target Location: %s"), units.Num(), *Hit.Location.ToString());
					for (int i = 0 ; i < units.Num(); i++)
					{
						ServerMoveToLocationStarted(units[i],Hit.Location);
						//units[i]->ServerMoveToLocationStarted(Hit.Location);

					}
				}
			}
		}
	}
}

