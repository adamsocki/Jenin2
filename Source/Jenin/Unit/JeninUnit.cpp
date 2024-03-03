// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUnit.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Components/Image.h"
#include "Jenin/Player/JeninPlayerController.h"
#include "Jenin/UI/JeninMarqueeHUD.h"
#include "Jenin/UI/Jenin_SelectedUnitWidget.h"


// Sets default values
AJeninUnit::AJeninUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* UnitCapsuleComponent = GetCapsuleComponent();
	UnitCapsuleComponent->SetCapsuleHalfHeight(44.0f);
	UnitCapsuleComponent->SetCapsuleRadius(20.0f);

	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(UnitCapsuleComponent);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> SelectedMaterialAsset(TEXT("Material'/Game/App/Materials/MAT_JeninSelectionDecal.MAT_JeninSelectionDecal'")); 
	if (SelectedMaterialAsset.Succeeded())
	{
		SelectionDecal->SetDecalMaterial(SelectedMaterialAsset.Object);
		SelectionDecalMaterial = SelectedMaterialAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> HighlightedSelectedMaterialAsset(TEXT("Material'/Game/App/Materials/MAT_JeninSelectionDecalHighlight.MAT_JeninSelectionDecalHighlight'")); 
	if (HighlightedSelectedMaterialAsset.Succeeded())
	{
		HighlightedDecalMaterial = HighlightedSelectedMaterialAsset.Object;
	}
	
}

void AJeninUnit::SelectUnit_Implementation()
{
	IJenin_RTSInterface::SelectUnit_Implementation();
	SelectionDecal->SetVisibility(true);
	AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (MarqueeHUD && MyUnitWidget)
	{
		MarqueeHUD->AddUnitToSelectedUnitsArea_Implementation(MyUnitWidget);
	}
}


void AJeninUnit::DeselectUnit_Implementation()
{
	IJenin_RTSInterface::DeselectUnit_Implementation();
	SelectionDecal->SetVisibility(false);
	if (MyUnitWidget)
	{
		MyUnitWidget->RemoveFromParent();
	}
}

void AJeninUnit::UnitMoveCommand_Implementation(FVector Location)
{

	IJenin_RTSInterface::UnitMoveCommand_Implementation(Location);
	if (AAIController *UnitAIController = GetController<AAIController>())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitMov AIController Unit."));
		//UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand_Implementation called. Location: %s"), *Location.ToString());

		UnitAIController->StopMovement();
		UnitAIController->MoveToLocation(Location);
	}
}

void AJeninUnit::HighlightUnit_Implementation()
{
	IJenin_RTSInterface::HighlightUnit_Implementation();
	SelectionDecal->SetDecalMaterial(HighlightedDecalMaterial);
}

void AJeninUnit::UnhighlightUnit_Implementation()
{
	IJenin_RTSInterface::UnhighlightUnit_Implementation();
	SelectionDecal->SetDecalMaterial(SelectionDecalMaterial);

}

// Called when the game starts or when spawned
void AJeninUnit::BeginPlay()
{
	 Super::BeginPlay();
	 MyUnitWidget = CreateWidget<UJenin_SelectedUnitWidget>(GetWorld(), UnitWidget);

	 if (MyUnitWidget)
	 {
		 MyUnitWidget->ActorReference = this;
	 	if (UnitImage)
	 	{
	 		MyUnitWidget->UnitImage->SetBrushFromTexture(UnitImage);
	 	}
	 }
}

// Called every frame
void AJeninUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AJeninUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

