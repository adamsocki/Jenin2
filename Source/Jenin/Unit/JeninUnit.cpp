﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninUnit.h"
#include "Net/UnrealNetwork.h"

#include "AIController.h"
#include "EngineUtils.h"
#include "Actions/JeninUnitActionWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Components/Image.h"
#include "Jenin/Player/JeninPlayerController.h"
#include "Jenin/UI/JeninMarqueeHUD.h"
#include "Jenin/UI/Jenin_SelectedUnitWidget.h"
#include "Kismet/GameplayStatics.h"



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

	
	ResourceOverlapper = CreateDefaultSubobject<UBoxComponent>(TEXT("ResourceOverlapper"));
	ResourceOverlapper->SetupAttachment(UnitCapsuleComponent);

	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bReplicates = true;
	bAlwaysRelevant = true;

	IsUnitWorking = false;
	HasResource = false;
}
void AJeninUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJeninUnit, TeamNumber);
	DOREPLIFETIME(AJeninUnit, TeamColor);   
}

void AJeninUnit::SelectThis_Implementation()
{
	IJenin_RTSInterface::SelectThis_Implementation();
	SelectionDecal->SetVisibility(true);
	AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (MarqueeHUD && MyUnitWidget)
	{
		if (MyUnitWidget)
		{
			if (Cast<IJenin_RTSInterface>(MarqueeHUD))
			{
				Execute_AddUnitToSelectedUnitsArea(MarqueeHUD, MyUnitWidget);
			}
		}
	
		for (int i = 0; i < MyUnitActionWidgets.Num(); i++)
		{
			if (UJeninUnitActionWidget* JeninUnitActionWidget = Cast<UJeninUnitActionWidget>(MyUnitActionWidgets[i]))
			{
				Execute_AddUnitActionsToSelectedUnitActionsArea(MarqueeHUD, JeninUnitActionWidget);
			}
		}
	}
}


void AJeninUnit::DeselectThis_Implementation()
{
	IJenin_RTSInterface::DeselectThis_Implementation();
	SelectionDecal->SetVisibility(false);
	if (MyUnitWidget)
	{
		MyUnitWidget->RemoveFromParent();
	}
	
	for (int i = 0; i < MyUnitActionWidgets.Num(); i++)
	{
		if (MyUnitActionWidgets[i])
		{
			if (AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
			{
				if (Cast<IJenin_RTSInterface>(MarqueeHUD))
				{
					Execute_RemoveUnitActionWidget(MarqueeHUD, MyUnitActionWidgets[i]);
					//Execute_RemoveActionWidget(MarqueeHUD, MyUnitActionWidgets[i]->ParentUnitAction->UnitActionDeExecution());
					MyUnitActionWidgets[i]->ParentUnitAction->UnitActionDeExecution();
				}
			}
		}
		MyUnitActionWidgets[i]->RemoveFromParent();
	}
}

void AJeninUnit::UnitMoveCommand_Implementation(FVector Location)
{
	IJenin_RTSInterface::UnitMoveCommand_Implementation(Location);
	if (AAIController *UnitAIController = GetController<AAIController>())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitMov AIController Unit."));
		//UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand_Implementation called. Location: %s"), *Location.ToString());
		if (HasAuthority()) // or Role == ROLE_Authority
		{
			//UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand executing on SERVER for %s"), *GetName());
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

void AJeninUnit::Collect_Implementation()
{
	IJeninResourceInterface::Collect_Implementation();

	if (IsUnitWorking)
	{
		if (HasResource) // Already has resource, go to dropoff
		{
			UE_LOG(LogTemp, Warning, TEXT("Has Resource TRUE"));
			Execute_UnitMoveCommand(this, DropOffBuilding->GetActorLocation());
		}
		else
		{	//  **********
			//	IF THE UNIT IS NOT CURRENTLY WORKING, THEN IT WILL START A TIMER FOR HOW LONG TO WORK
			//	ONCE THE TIMER IS COMPLETED, IT WILL GO TO THE LOCATION USING resourceCollected FUNCTION
			//	TODO -> MAKE A CUSTOM FINISH TYPE WHICH CAN BE CONTAINED IN THE WORKING OBJECT THAT THE UNIT IS ENGAGED WITH
			UE_LOG(LogTemp, Warning, TEXT("Has Resource FALSE"));

			Execute_UnitMoveCommand(this, this->GetActorLocation());
			
			float TimerInterval = 4.0f;  
			bool bShouldLoop = false;

			GetWorldTimerManager().SetTimer(TimerHandle, this, &AJeninUnit::ResourceCollected, TimerInterval, bShouldLoop);
			if (!TimerHandle.IsValid())
			{
				
			}
		}
	}
}

void AJeninUnit::DropOff_Implementation()
{
	IJeninResourceInterface::DropOff_Implementation();
	if (IsUnitWorking)
	{
		if(HasResource)
		{
			if (AJeninPlayerController* JeninPlayerController = Cast<AJeninPlayerController>(UGameplayStatics::GetPlayerController(this, TeamNumber)))
			{
				if (IJenin_RTSInterface* JeninInterface = Cast<IJenin_RTSInterface>(JeninPlayerController))
				{
					Execute_IncrementResourceAmount(JeninPlayerController, 1);
					UE_LOG(LogTemp, Warning, TEXT("Execute_IncrementResourceAmount"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Unit DOES NOT HAVE A PLAYER CONTROLLER ASSIGNED"));
			}
			HasResource = false;
			Execute_UnitMoveCommand(this, ResourceNodeWorkingFrom->GetActorLocation());
		}
		else
		{
			Execute_UnitMoveCommand(this, ResourceNodeWorkingFrom->GetActorLocation());
		}
	}
}

void AJeninUnit::SetIsWorkingOnResource_Implementation(AJeninResourceNode* ResourceNode)
{
	IJeninResourceInterface::SetIsWorkingOnResource_Implementation(ResourceNode);

	IsUnitWorking = true;
	
	ResourceNodeWorkingFrom = ResourceNode;

	TArray<AActor*> FoundBuildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AJeninBuilding::StaticClass(), FoundBuildings);

	// find nearest dropoff point
	float ClosestDistanceDropoffBuilding = 50000;

	for (int i = 0; i < FoundBuildings.Num(); i++)
	{
		if (AJeninBuilding* CurrentBuilding = Cast<AJeninBuilding>(FoundBuildings[i]))
		{
			// UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), i);
			if (CurrentBuilding->GetClass()->ImplementsInterface(UJenin_RTSInterface::StaticClass()))
			{	
				UE_LOG(LogTemp, Warning, TEXT("The Distacne value is: %f"), CurrentBuilding->GetDistanceTo(this));
				if (TeamNumber == Execute_GetTeam(CurrentBuilding))
				{
					UE_LOG(LogTemp, Warning, TEXT("Building on team found!!!"));

					float CurrentBuildingDistance = CurrentBuilding->GetDistanceTo(this);
					if ( CurrentBuildingDistance < ClosestDistanceDropoffBuilding)
					{
						ClosestDistanceDropoffBuilding = CurrentBuildingDistance;
						DropOffBuilding = CurrentBuilding;
						UE_LOG(LogTemp, Warning, TEXT("DropOffBuilding found!!!"));
					}
				}
			}
		}
	}

	// MOVE TO RESOURCES OR BUILDING 
	if (HasResource)
	{
		Execute_UnitMoveCommand(this, DropOffBuilding->GetActorLocation());
	}
	else
	{
		Execute_UnitMoveCommand(this, ResourceNodeWorkingFrom->GetActorLocation());
	}
}

void AJeninUnit::SetNotWorking_Implementation()
{
	IJeninResourceInterface::SetNotWorking_Implementation();

	//IsUnitWorking = false;
	//TimerHandle.Invalidate();
	
}

void AJeninUnit::ServerMoveToLocationStarted_Implementation(FVector Location)
{
	if (HasAuthority()) // or Role == ROLE_Authority
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand executing on SERVER for %s"), *GetName());
		AAIController *UnitAIController = GetController<AAIController>();
		if (UnitAIController)
		{
			UE_LOG(LogTemp, Warning, TEXT("UnitMov AIController Unit."));
			UnitAIController->StopMovement();
			UnitAIController->MoveToLocation(Location);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No AI CONTROLLER FOR UNIT."));
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand executing on CLIENT for %s"), *GetName());
	}
	if (AAIController *UnitAIController = GetController<AAIController>())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitMov AIController Unit."));
		//UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand_Implementation called. Location: %s"), *Location.ToString());
		
		UnitAIController->StopMovement();
		UnitAIController->MoveToLocation(Location);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI CONTROLLER FOR UNIT."));

	}
	UE_LOG(LogTemp, Warning, TEXT("ServerUpdate for move."));
}

// Called when the game starts or when spawned
void AJeninUnit::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (SkeletalMeshComponent)
	{
		UMaterialInterface* Material_0 = SkeletalMeshComponent->GetMaterial(0);
		if (Material_0)
		{
			UMaterialInstanceDynamic* MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(Material_0, NULL);
			MaterialInstanceDynamic->SetVectorParameterValue("ColorPanel",TeamColor);
			SkeletalMeshComponent->SetMaterial(0, MaterialInstanceDynamic);
		}
	}

	MyUnitWidget = CreateWidget<UJenin_SelectedUnitWidget>(GetWorld(), UnitWidget);

	if (MyUnitWidget)
	{
		MyUnitWidget->ActorReference = this;
		if (UnitImage)
		{
			MyUnitWidget->UnitImage->SetBrushFromTexture(UnitImage);
		}
	}

	for (int i = 0; i < UnitActions.Num(); i++)
	{
		if (UnitActions[i] != nullptr)
		{
			// Instantiate the object using the class from the array
			UJeninUnitAction* NewJeninUnitActionInstance = NewObject<UJeninUnitAction>(this, UnitActions[i]);
			if (NewJeninUnitActionInstance != nullptr)
			{
				// Add the new instance to the InstantiatedObjects array
				MyUnitActions.Add(NewJeninUnitActionInstance);
				if (UWorld* GameWorld = GetWorld())
				{
					if (UJeninUnitActionWidget* NewJeninUnitActionWidgetInstance = CreateWidget<UJeninUnitActionWidget>(GameWorld, NewJeninUnitActionInstance->UnitActionWidget))
					{
						MyUnitActionWidgets.Add(NewJeninUnitActionWidgetInstance);
						NewJeninUnitActionWidgetInstance->ParentUnitAction = NewJeninUnitActionInstance;
						NewJeninUnitActionInstance->InitUnitAction();
						// UE_LOG(LogTemp, Warning, TEXT("NewUnitActionWidgetInstancd"));
					}
				}
				
			}
		}
	}
	
	// for (int i = 0; i < UnitActions.Num(); i++)
	// {
	// 	UJeninUnitActionWidget* MyUnitActionWidget = CreateWidget<UJeninUnitActionWidget>(GetWorld(), UnitActions[i]);
	// 	if (MyUnitActionWidget)
	// 	{
	// 		MyUnitActionWidgets.Add(MyUnitActionWidget);
	// 	}
	// }

	// for (int i = 0; i < UnitActionsObjects.Num(); i++)
	// {
	// 	if (UJeninUnitAction* UnitAction = UnitActionsObjects[i].Get())
	// 	{
	// 		if (UWorld* GameWorld = GetWorld())
	// 		{
	// 			if (UJeninUnitActionWidget* NewUnitActionWidgetInstance = CreateWidget<UJeninUnitActionWidget>(GameWorld, UnitAction->UnitActionWidget))
	// 			{
	// 				MyUnitActionWidgets.Add(NewUnitActionWidgetInstance);
	// 				NewUnitActionWidgetInstance->ParentUnitAction = UnitAction;
	// 				UnitAction->InitUnitAction();
	// 			}
	// 		}
	// 	}
	// }
}
			
			// Instantiate the object using the class from the array
			//''UJeninUnitAction* NewJeninUnitActionInstance = NewObject<UJeninUnitAction>(this, UnitActionsObjects[i]);
		// 	if (NewJeninUnitActionInstance != nullptr)
		// 	{
		// 		// Add the new instance to the InstantiatedObjects array
		// 		//MyUnitActions.Add(NewJeninUnitActionInstance);
		// 		if (UWorld* GameWorld = GetWorld())
		// 		{
		// 			if (UJeninUnitActionWidget* NewUnitActionWidgetInstance = CreateWidget<UJeninUnitActionWidget>(GameWorld, NewJeninUnitActionInstance->UnitActionWidget))
		// 			{
		// 				MyUnitActionWidgets.Add(NewUnitActionWidgetInstance);
		// 				NewUnitActionWidgetInstance->ParentUnitAction = NewJeninUnitActionInstance;
		// 				NewJeninUnitActionInstance->InitUnitAction();
		// 				// UE_LOG(LogTemp, Warning, TEXT("NewUnitActionWidgetInstancd"));
		// 				
		//
		// 			}
		// 		}
		// 		
		// 	}
		// }

	


// Optionally, call any initialization or setup functions on your new object
				//NewObjInstance->DoSomething();
		//UJeninUnitAction* JeninUnitAction = NewObject<UJeninUnitAction>(this,)
		// UObject* ArrayElement = UnitActions[i];
		// UClass* ElementClass = ArrayElement->GetClass();
		// UE_LOG(LogTemp, Warning, TEXT("ElementClass is: %s"), *ElementClass->GetName());

		// if (UnitActions[i] != nullptr)
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("Object Info: %s"), *UnitActions[i]->GetFullName());
		// }
		// else
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("UnitActionArray[i] is nullptr"));
		// }
		// if (TSoftObjectPtr<UJeninUnitAction> SoftPtr = UnitActions[i])
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("UnitActions.Num()"));
		// 	UE_LOG(LogTemp, Warning, TEXT("UnitActions.Num()"));
		// 	UE_LOG(LogTemp, Warning, TEXT("UnitActions.Num()"));
		// 	UE_LOG(LogTemp, Warning, TEXT("UnitActions.Num()"));
		//
		// 	if (UJeninUnitActionWidget* MyUnitActionWidget = CreateWidget<UJeninUnitActionWidget>(GetWorld(), SoftPtr->UnitActionWidget))
		// 	{
		// 		MyUnitActionWidgets.Add(MyUnitActionWidget);
		// 	}
		// }
	

	
	// for (TActorIterator<APlayerController> It(GetWorld()); It; ++It)
	// {
	// 	
	// 	UE_LOG(LogTemp, Warning, TEXT("The this->TeamNumber value is: %d"), this->TeamNumber);
	// 	APlayerController* PlayerController = *It;
	// 	// GetController()
	// 	if (AJeninPlayerController* JeninPlayerController = Cast<AJeninPlayerController>(PlayerController))
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("The JeninPlayerController->TeamNumber value is: %d"), JeninPlayerController->TeamNumber);
     	// 		if (JeninPlayerController->TeamNumber == this->TeamNumber) 
	// 		{
	// 			UnitsJeninPlayerController = JeninPlayerController;
	// 			break; 
	// 		}
	// 	}
	// }


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

int32 AJeninUnit::GetTeam_Implementation()
{
	return TeamNumber;
}


void AJeninUnit::BeginDestroy()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is being destroyed!"), *GetName());
	//UE_LOG(LogTemp, Warning, TEXT("%s is being destroyed! Owner: %s, IsPendingKill: %d"), *GetName(), *GetNameSafe(GetOwner()), IsPendingKill());
   
	// ... potentially more detailed logging here ...
	Super::BeginDestroy(); 
}

void AJeninUnit::ResourceCollected()
{
	TimerHandle.Invalidate();
	UE_LOG(LogTemp, Warning, TEXT("The integer value is: ResourceCollected"));
	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *DropOffBuilding->GetActorLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *this->GetActorLocation().ToString());
	HasResource = true;
	Execute_UnitMoveCommand(this, DropOffBuilding->GetActorLocation());
}

