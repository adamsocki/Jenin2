// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninResourceInterface.h"
#include "../../../../../../epic/engine/UE_5.3/Engine/Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
//#include "Components/PrimitiveComponent.h"
#include "JeninResourceNode.generated.h"

UCLASS()
class JENIN_API AJeninResourceNode : public AActor, public IJeninResourceInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
public:
	// Sets default values for this actor's properties
	AJeninResourceNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
