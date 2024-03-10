// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninCameraPawn.h"

#include "EnhancedInputSubsystems.h"

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
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		FVector MousePosition = {};
		int32 ViewportSizeX = {};
		int32 ViewportSizeY = {};
		PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
		PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

		
		if (IsOverTopEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = ScrollSpeed * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -ScrollSpeed * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverLeftEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.Y = -ScrollSpeed * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverRightEdge)
		{
			FVector DeltaLocation = {};
			DeltaLocation.Y = ScrollSpeed * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverTopLeft)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X =  (ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y = -(ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverTopRight)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X =  (ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y =  (ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomLeft)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -(ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y = -(ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
		else if (IsOverBottomRight)
		{
			FVector DeltaLocation = {};
			DeltaLocation.X = -(ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			DeltaLocation.Y =  (ScrollSpeed * GetWorld()->GetDeltaSeconds() * 0.67 );
			AddActorWorldOffset(DeltaLocation);
		}
		//
		// if (MousePosition.Y / ViewportSizeY > 0.98f)
		// {
		// 	FVector DeltaLocation = {};
		// 	DeltaLocation.X = -ScrollSpeed * GetWorld()->GetDeltaSeconds();
		// 	AddActorWorldOffset(DeltaLocation);
		// }
		// else if (MousePosition.Y / ViewportSizeX < 0.02f)
		// {
		// 	FVector DeltaLocation = {};
		// 	DeltaLocation.X = ScrollSpeed * GetWorld()->GetDeltaSeconds();
		// 	AddActorWorldOffset(DeltaLocation);
		// }
		// if (MousePosition.X >= 0 && MousePosition.X <= ViewportSizeX &&
		//    MousePosition.Y >= 0 && MousePosition.Y <= ViewportSizeY)
		// {
		
		// }
	}
}

// Called to bind functionality to input
void AJeninCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	
}

