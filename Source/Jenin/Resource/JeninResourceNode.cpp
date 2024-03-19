// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninResourceNode.h"


// Sets default values
AJeninResourceNode::AJeninResourceNode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = MyRoot;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh->SetCanEverAffectNavigation(false);

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AJeninResourceNode::OnOverlapBegin);
	StaticMesh->CanCharacterStepUpOn = ECB_No;

	//StaticMesh->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void AJeninResourceNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeninResourceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJeninResourceNode::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority() && OtherActor->GetClass()->ImplementsInterface(UJeninResourceInterface::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ONOverlap"));
		Execute_Collect(OtherActor);
	}
}

