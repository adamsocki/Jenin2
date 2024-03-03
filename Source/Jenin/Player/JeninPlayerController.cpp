// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninPlayerController.h"
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

void AJeninPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
					UE_LOG(LogTemp, Warning, TEXT("Hello"));
					SelectedBuilding = Cast<AJeninBuilding>(HitResult.GetActor());
					SelectedBuilding->SelectThis_Implementation();
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
						units[i]->UnitMoveCommand_Implementation(Hit.Location);
					}
				}
			}
		}
	}
}