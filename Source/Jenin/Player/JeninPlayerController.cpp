// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninPlayerController.h"

#include "AIController.h"
#include "Net/UnrealNetwork.h"
#include "DetourCrowdAIController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JeninCameraPawn.h"
#include "Components/HorizontalBox.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/Resource/JeninResourceInterface.h"
#include "Jenin/Resource/JeninResourceNode.h"
#include "Jenin/UI/JeninMarqueeHUD.h"

AJeninPlayerController::AJeninPlayerController()
{
	ClickedLocation = {};
	IsLeftMouseButtonPressed = {};
	MiddleMouseButtonDown = false;
	LeftShiftButtonDown = false;

	MouseZoomSpeed = 1000.0f;
	bShowMouseCursor = false;
	
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
	DOREPLIFETIME(AJeninPlayerController, ResourceAmount);
}

void AJeninPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnLeftMouseStarted);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Completed, this, &AJeninPlayerController::OnLeftMouseCompleted);
		EnhancedInputComponent->BindAction(MoveToLocationAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnMoveToLocationStarted);
		
		EnhancedInputComponent->BindAction(MouseScrollWheelAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnMouseScrollWheel);
		
		EnhancedInputComponent->BindAction(MouseMiddleButtonAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::OnMiddleMousePressed);
		EnhancedInputComponent->BindAction(MouseMiddleButtonAction, ETriggerEvent::Completed, this, &AJeninPlayerController::OnMiddleMouseReleased);

		
		EnhancedInputComponent->BindAction(LeftShiftAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnLeftShiftPressed);
		EnhancedInputComponent->BindAction(LeftShiftAction, ETriggerEvent::Completed, this, &AJeninPlayerController::OnLeftShiftReleased);

		
		//EnhancedInputComponent->BindAction(MouseAxisAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::MouseAxisModify);

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
	UE_LOG(LogTemp, Warning, TEXT("This shouldng happen yet"));
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
		//SpawnUnit001Parameters.Owner = this;
		
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



void AJeninPlayerController::ProduceUnit_Implementation(AJeninBuilding* buildingReference, TSubclassOf<AJeninUnit> UnitToProduce)
{
	IJenin_RTSInterface::ProduceUnit_Implementation(buildingReference, UnitToProduce);
	ServerProduceUnit(buildingReference, UnitToProduce);
}

void AJeninPlayerController::ServerProduceUnit_Implementation(AJeninBuilding* BuildingReference,
	TSubclassOf<AJeninUnit> UnitToProduce)
{
	// @todo now: ask building to produce unit
	UE_LOG(LogTemp, Warning, TEXT("ServerProduceUnit_Implementation"));

	BuildingReference->AddUnitToQueue(UnitToProduce);
}


int32 AJeninPlayerController::GetResourceAmount_Implementation()
{
	//return IJenin_RTSInterface::GetResourceAmount_Implementation();
	return ResourceAmount;
}

void AJeninPlayerController::IncrementResourceAmount_Implementation(int32 Amount)
{
	ResourceAmount += Amount;
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
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
		InputMode.SetHideCursorDuringCapture(false);
		this->SetInputMode(InputMode);
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// if (EdgeScrollWidget)
	// {
	// 	MyEdgeScrollWidget = CreateWidget<UJeninEdgeScroll>(GetWorld(), EdgeScrollWidget);
	// 	MyEdgeScrollWidget->AddToViewport();
	// 	
	// }

	
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
					if (this->GetClass()->ImplementsInterface(UJenin_RTSInterface::StaticClass()))
					{
						if (IJenin_RTSInterface::Execute_IsOnMyTeam(this, BuildingTeam))
						{
							if (SelectedBuilding->GetClass()->ImplementsInterface(UJenin_RTSInterface::StaticClass()))
							{
								IJenin_RTSInterface::Execute_SelectThis(SelectedBuilding);
							}
							UE_LOG(LogTemp, Warning, TEXT("SelectThisSholundwixk"));
							
						}
						
					}
					
				}
			}
			AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
			if (MarqueeHUD) 
			{
				IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD);
				if (JeninInterface)
				{
					IJenin_RTSInterface::Execute_MarqueeHeld(MarqueeHUD);
					//JeninInterface->MarqueeHeld_Implementation();
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
		if (AJeninResourceNode* JeninResourceNode = Cast<AJeninResourceNode>(Hit.GetActor()))
		{
			AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
			if (MarqueeHUD)
			{
				IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD);
				if (JeninInterface)
				{
					TArray<AJeninUnit*> units = JeninInterface->GrabSelectedUnits_Implementation();

					for (int i = 0 ; i < units.Num(); i++)
					{
						if (units[i]->GetClass()->ImplementsInterface(UJeninResourceInterface::StaticClass()))
						{
							ServerPassThroughSetIsWorking(units[i], JeninResourceNode);

						}
						//ServerMoveToLocationStarted(units[i],Hit.Location);
						//units[i]->ServerMoveToLocationStarted(Hit.Location);
					}
				}
			}
		}
		else
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
}

void AJeninPlayerController::OnMouseScrollWheel(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0.0f)
	{
		float ZoomSpeedApply = 500.0f;
		if (LeftShiftButtonDown)
		{
			ZoomSpeedApply *= 4.0f;
		}
		AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetPawn());
		
		JeninCameraPawn->Target_TargetArmLength = FMath::Clamp(JeninCameraPawn->SpringArm->TargetArmLength + Value.GetMagnitude() * - ZoomSpeedApply, 10.0f, 60000.0f);
	}
	

	// FVector CameraPosition = JeninCameraPawn->GetActorLocation();
	// CameraPosition.Z = CameraPosition.Z + Value.Get<float>() * MouseZoomSpeed * GetWorld()->GetDeltaSeconds();
	// JeninCameraPawn->SetActorLocation(CameraPosition);
	// UE_LOG(LogTemp, Warning, TEXT("Scroll"));
	//
	// FVector DeltaLocation = {};
	// DeltaLocation.Z = MouseZoomSpeed *Value.Get<float>();
	// JeninCameraPawn->AddActorWorldOffset(DeltaLocation);
	// // @TODO -> Get Distance to ground to prevent going below terrain  

}

void AJeninPlayerController::OnMiddleMousePressed(const FInputActionValue& Value)
{
	MiddleMouseButtonDown = true;
	UE_LOG(LogTemp, Warning, TEXT("OnMiddleMousePressed"));
	FVector CurrentAxis = InputComponent->GetVectorAxisValue(FName("MouseAxisMapping"));  // Replace "MoveForward" with your actual axis name
	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *CurrentAxis.ToString());
}

void AJeninPlayerController::OnMiddleMouseReleased(const FInputActionValue& Value)
{
	MiddleMouseButtonDown = false;
	UE_LOG(LogTemp, Warning, TEXT("OnMiddleMouseReleased"));
}

void AJeninPlayerController::OnLeftShiftPressed(const FInputActionValue& Value)
{
	LeftShiftButtonDown = true;
	UE_LOG(LogTemp, Warning, TEXT("OnLeftShiftPressed"));

}

void AJeninPlayerController::OnLeftShiftReleased(const FInputActionValue& Value)
{
	LeftShiftButtonDown = false;
	UE_LOG(LogTemp, Warning, TEXT("OnLeftShiftReleased"));
}

// void AJeninPlayerController::MouseAxisModify(const FInputActionValue& Value)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *Value.Get<FVector2D>().ToString());
// 	UE_LOG(LogTemp, Warning, TEXT("MouseAxisModify triggered! Vector value: %s"), *Value.Get<FVector2D>().ToString());
//
// }


void AJeninPlayerController::ServerPassThroughSetIsWorking_Implementation(AJeninUnit* Unit,
                                                                          AJeninResourceNode* ResourceNode)
{
	if (IJeninResourceInterface* JeninResourceInterface = Cast<IJeninResourceInterface>(Unit))
	{
		JeninResourceInterface->Execute_SetIsWorkingOnResource(Unit, ResourceNode);
	}
	
}
