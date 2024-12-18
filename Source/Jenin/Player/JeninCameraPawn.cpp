// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninCameraPawn.h"

#include "EnhancedInputSubsystems.h"
#include "JeninPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AJeninCameraPawn::AJeninCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraBoxComponent"));
	CameraBoxComponent->SetupAttachment(RootComponent);

	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	this->SpringArm->SetupAttachment(CameraBoxComponent);

	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bEnableCameraLag = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	this->Camera->SetupAttachment(this->SpringArm);

	FRotator NewRotation = FRotator(70.0f, 0.0f, 0.0f); // Construct rotator with desired values
	Camera->SetRelativeRotation(NewRotation);

	IsOverBottomEdge = false;
	SpringArm->bEnableCameraLag = true;
}

// Called when the game starts or when spawned
void AJeninCameraPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AJeninCameraPawn::MoveCamera(FVector3d MovementInput)
{
	if (AJeninPlayerController* JeninPlayerController = Cast<AJeninPlayerController>(Controller))
	{
		float TraceDistance = 8000.0f;

		FHitResult HitResult;
		FVector StartLocation = CameraBoxComponent->GetComponentLocation();
		FVector EndLocation = StartLocation + FVector::DownVector * TraceDistance;
		// TraceDistance is how far down you want to trace
		//
		FCollisionQueryParams CP = {};
		TArray<AActor*> ActorsToIgnore = {};
		//
		bool bTraceHit = ActorLineTraceSingle(HitResult, StartLocation, EndLocation, ECC_WorldStatic, CP);
		if (bTraceHit)
		{
			//			HitResult.Distance;=
		}

		// bool bTraceHit = UKismetSystemLibrary::LineTraceSingle(
		// 	GetWorld(), 
		// 	StartLocation, 
		// 	EndLocation, 
		// 	ETraceTypeQuery::TraceTypeQuery1, // Adjust the trace channel as needed
		// 	false,  // Whether to ignore simple collisions
		// 	ActorsToIgnore, // Array of actors to ignore in the trace
		// 	EDrawDebugTrace::ForDuration, // Use this to visualize the trace
		// 	HitResult, 
		// 	true, 
		// 	FLinearColor::Red, 
		// 	FLinearColor::Green, 
		// 	5.0f // Line trace thickness
		// );

		// float DesiredHeightOffset = 1000.0f;
		// float InterpSpeed = 5.0f; // Adjust this for desired camera movement smoothness
		//
		// if (bTraceHit)
		// {
		// 	float DistanceToGround = (StartLocation - HitResult.Location).Z;
		// 	// Use DistanceToGround to adjust the camera's Z position
		// 	FVector TargetCameraLocation = CameraBoxComponent->GetComponentLocation();
		// 	TargetCameraLocation.Z = StartLocation.Z - DistanceToGround + DesiredHeightOffset; // DesiredHeightOffset is a constant you'd set for your preferred camera height.
		// 	FVector NewCameraLocation = FMath::VInterpTo(CameraBoxComponent->GetComponentLocation(), TargetCameraLocation, GetWorld()->DeltaTimeSeconds, InterpSpeed);
		// 	CameraBoxComponent->SetWorldLocation(TargetCameraLocation);
		// }


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

		// ***********************
		// KEYBOARD INPUT MOVEMENT
		// ***********************
		if (MovementInput.X != 0 || MovementInput.Y != 0 || MovementInput.Z != 0)
		{
			FVector WorldMovement = MovementInput * ScrollSpeedToApply * GetWorld()->GetDeltaSeconds();
			// WorldMovement.X = MovementInput.X * ScrollSpeedToApply;

			// Apply world Z movement
			AddActorWorldOffset(WorldMovement, true);
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
			DeltaLocation.X = (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			DeltaLocation.Y = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverTopRight)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			DeltaLocation.Y = (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomLeft)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			DeltaLocation.Y = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomRight)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -(ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			DeltaLocation.Y = (ScrollSpeedToApply * GetWorld()->GetDeltaSeconds() * 0.67);
			AddActorWorldOffset(DeltaLocation);
		}
	}
}

// Called every frame
void AJeninCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// CAMERA MOVEMENT AT EDGE OF VIEWPORT

	MoveCamera(KeyboardMovementVector);

	KeyboardMovementVector = FVector::ZeroVector;

	// FloatInter

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, Target_TargetArmLength, DeltaTime, 5.0f);
}

// Called to bind functionality to input
void AJeninCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
