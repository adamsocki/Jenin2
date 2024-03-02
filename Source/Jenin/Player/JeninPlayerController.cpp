// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/HorizontalBox.h"
#include "Jenin/Core/Jenin_RTSInterface.h"
#include "Jenin/UI/JeninMarqueeHUD.h"

// #include "Jenin/UI/JeninMarqueeHUD.h"


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

void AJeninPlayerController::BeginPlay()
{
	Super::BeginPlay();
	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true; // Allows clicks 
	this->bEnableMouseOverEvents = true; // Allows mouse-over events
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
		AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
		if (MarqueeHUD) 
		{
			IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD); // Cast to your interface type
			if (JeninInterface)
			{
				JeninInterface->MarqueeHeld_Implementation();  // Call the interface function!
			}   
		} 
	}
}

void AJeninPlayerController::OnLeftMouseStarted(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("OnLeftMouseStarted Called!"));
	IsLeftMouseButtonPressed = true;
	AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetHUD());
	if (MarqueeHUD) 
	{
		IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(MarqueeHUD); // Cast to your interface type
		if (JeninInterface)
		{
			JeninInterface->MarqueePressed_Implementation();  // Call the interface function!
			
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
	//UE_LOG(LogTemp, Warning, TEXT("onmovestarted."));

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

