// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninCameraPawn.h"

#include "EnhancedInputSubsystems.h"
#include "JeninPlayerController.h"

// Sets default values
AJeninCameraPawn::AJeninCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	this->SpringArm->SetupAttachment(RootComponent);

	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bEnableCameraLag = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	this->Camera->SetupAttachment(this->SpringArm);
	
	FRotator NewRotation = FRotator(70.0f, 0.0f, 0.0f); // Construct rotator with desired values
	Camera->SetRelativeRotation(NewRotation);

	IsOverBottomEdge = false;
	SpringArm->bEnableCameraLag = true;
	Target_TargetArmLength = 100.0f;
}

// Called when the game starts or when spawned
void AJeninCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	
}



// Called every frame
void AJeninCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// CAMERA MOVEMENT AT EDGE OF VIEWPORT
	if(AJeninPlayerController* JeninPlayerController = Cast<AJeninPlayerController>(Controller))
	{
		FVector MousePosition = {};
		int32 ViewportSizeX = {};
		int32 ViewportSizeY = {};
		JeninPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
		JeninPlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

		// @TODO -> Get Distance to floor to scale speed 
		// @TODO -> Get Distance to move up/down for terrain adjustment

		float ScrollSpeedToApply = ScrollSpeed;
		if (JeninPlayerController->LeftShiftButtonDown)
		{
			ScrollSpeedToApply *= 4;
			
		}
		
			

		if (IsOverTopEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = ScrollSpeedToApply * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -ScrollSpeedToApply * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverLeftEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.Y = -ScrollSpeedToApply * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverRightEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.Y = ScrollSpeedToApply * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverTopLeft)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X =  (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverTopRight)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X =  (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y =  (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomLeft)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomRight)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y =  (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
	}

 // FloatInter
	
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, Target_TargetArmLength, DeltaTime, 5.0f);
}

// Called to bind functionality to input
void AJeninCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

