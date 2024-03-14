// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninBuilding.h"
#include "Net/UnrealNetwork.h"

#include "Components/DecalComponent.h"
#include "Jenin/UI/JeninProduceUnitWidget.h"
#include "Jenin/Unit/JeninUnit.h"

// Sets default values
AJeninBuilding::AJeninBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = MyRoot;
	
	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);
	FVector DecalSize = FVector(50.0f, 100.0f, 100.0f);
	SelectionDecal->DecalSize = DecalSize;
	static ConstructorHelpers::FObjectFinder<UMaterial> SelectedMaterialAsset(TEXT("Material'/Game/App/Materials/MAT_JeninSelectionDecal.MAT_JeninSelectionDecal'")); 
	if (SelectedMaterialAsset.Succeeded())
	{
		SelectionDecal->SetDecalMaterial(SelectedMaterialAsset.Object);
		SelectionDecalMaterial = SelectedMaterialAsset.Object;
	}
	SelectionDecal->SetVisibility(false);

	UnitSpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("UnitSpawnPoint"));
	UnitSpawnPoint->SetupAttachment(RootComponent);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetReceivesDecals(false);
	
	bReplicates = true;
	bAlwaysRelevant=true;

	IsProducingUnit = false;
	ProductionTimeNeeded = 0.0f;
	ProductionTimeSpent = 0.0f;
	ProductionProgress = 0.0f;
}
void AJeninBuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJeninBuilding, TeamNumber);
	DOREPLIFETIME(AJeninBuilding, TeamColor);   
	DOREPLIFETIME(AJeninBuilding, UnitProductionQueue);
	DOREPLIFETIME(AJeninBuilding, ProductionProgress);
}


void AJeninBuilding::SelectThis_Implementation()
{
	IJenin_RTSInterface::SelectThis_Implementation();
	SelectionDecal->SetVisibility(true);
	MyBuildingSelectedWidget->AddToViewport();
}

void AJeninBuilding::DeselectThis_Implementation()
{
	IJenin_RTSInterface::DeselectThis_Implementation();
	SelectionDecal->SetVisibility(false);
	MyBuildingSelectedWidget->RemoveFromParent();
}

// Called when the game starts or when spawned
void AJeninBuilding::BeginPlay()
{
	Super::BeginPlay();

	MyBuildingSelectedWidget = CreateWidget<UJeninBuildingSelectedWidget>(GetWorld(), BuildingWidget);

	
	//for (Act)
	
	if (StaticMesh)
	{
		UMaterialInterface* Material_0 = StaticMesh->GetMaterial(0);
		if (Material_0)
		{
			UMaterialInstanceDynamic* MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(Material_0, NULL);
			MaterialInstanceDynamic->SetVectorParameterValue("TeamColor",TeamColor);
			StaticMesh->SetMaterial(0, MaterialInstanceDynamic);
		}
	}
	if (MyBuildingSelectedWidget)
	{
		MyBuildingSelectedWidget->ActorReference = this;
		// if (UnitImage)
		// {
		// 	MyUnitWidget->UnitImage->SetBrushFromTexture(UnitImage);
		// }
		// for (int i = 0; i < ActionBoxButtonWidgets.Num(); i++)
		// {
		// 	
		// 	UE_LOG(LogTemp, Warning, TEXT("UnitUNIT"));
		// }
		for (int i = 0; i < SpawnableUnits.Num(); i++)
		{
			if(UJeninProduceUnitWidget* NewWidget = CreateWidget<UJeninProduceUnitWidget>(MyBuildingSelectedWidget,ProductionWidget))
			{
				MyBuildingSelectedWidget->ActionBox->AddChildToWrapBox(NewWidget);
				NewWidget->BuildingReference = this;
				NewWidget->UnitToProduce = SpawnableUnits[i];
				NewWidget->SetVisibility(ESlateVisibility::Visible); 
			
			}
			//MyUnitWidget->BuildingReference = this;
			
			

			//ActionBoxButtonWidgets.AddUnique(MyUnitWidget);
			UE_LOG(LogTemp, Warning, TEXT("UnitAdd"));
	
		}
	}

	// HANDLE UNIT PRODUCTION QUEUE
	if (HasAuthority())
	{
		FTimerHandle TimerHandle;
		float TimerInterval = 0.05f;  // Example: Timer fires every 2 seconds
		bool bShouldLoop = true; // Whether it should repeat

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AJeninBuilding::ProcessProductionQueue, TimerInterval, bShouldLoop);

	}
	
}

// Called every frame
void AJeninBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 AJeninBuilding::GetTeam_Implementation()
{
	return TeamNumber;
}

void AJeninBuilding::AddUnitToQueue(TSubclassOf<AJeninUnit> NewUnit)
{
	UnitProductionQueue.Add(NewUnit);
	UE_LOG(LogTemp, Warning, TEXT("AddUnitToQueue"));

}

void AJeninBuilding::ProcessProductionQueue()
{

	if (IsProducingUnit)	
	{
		
		ProductionTimeSpent += ProductionUnitTimerGranularity;
		ProductionProgress = ProductionTimeSpent / ProductionTimeNeeded;
		UE_LOG(LogTemp, Log, TEXT("ProductionTimeSpent updated: %f"), ProductionTimeSpent);

		UE_LOG(LogTemp, Log, TEXT("ProductionProgress calculated: %f"), ProductionProgress);
		UE_LOG(LogTemp, Log, TEXT("ProductionTimeNeeded calculated: %f"), ProductionTimeNeeded);

		if (ProductionProgress >= 1.0f)
		{
			FActorSpawnParameters SpawnUnitParameters;
			SpawnUnitParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			//SpawnBuildingParameters.Owner = this;
			FRotator SpawnRotation = {};
			AJeninUnit* SpawnedUnit = GetWorld()->SpawnActor<AJeninUnit>(UnitToProduce, UnitSpawnPoint->GetComponentLocation(), SpawnRotation);
			SpawnedUnit->TeamNumber = TeamNumber;
			SpawnedUnit->TeamColor = TeamColor;

			ProductionProgress = 0.0f;
			ProductionTimeSpent = 0.0f;
			UnitToProduce = nullptr;
			IsProducingUnit = false;
		}
	}
	else if (UnitProductionQueue.Num() > 0)		// Get Unit from Queue
	{


		UnitToProduce = UnitProductionQueue[0]; 
		ProductionTimeNeeded = UnitToProduce->GetDefaultObject<AJeninUnit>()->ProductionTime;
		UE_LOG(LogTemp, Warning, TEXT("UnitProductionQueue.Num"));
		UnitProductionQueue.RemoveAt(0);
		IsProducingUnit = true;
		
	}
	
	
}

