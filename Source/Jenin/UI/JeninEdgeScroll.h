// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "JeninEdgeScroll.generated.h"

/**
 * PB
 */
UCLASS()
class JENIN_API UJeninEdgeScroll : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* BottomEdge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* BottomLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* BottomRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* TopEdge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* TopLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* TopRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* LeftEdge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* RightEdge;

	UFUNCTION()
	void OnMouseHoverBottomEdge();
	UFUNCTION()
	void OnMouseHoverBottomLeft();
	UFUNCTION()
	void OnMouseHoverBottomRight();
	UFUNCTION()
	void OnMouseHoverTopEdge();
	UFUNCTION()
	void OnMouseHoverTopLeft();
	UFUNCTION()
	void OnMouseHoverTopRight();
	UFUNCTION()
	void OnMouseHoverLeftEdge();
	UFUNCTION()
	void OnMouseHoverRightEdge();


	UFUNCTION()
	void OnMouseUnhoverBottomEdge();
	UFUNCTION()
	void OnMouseUnhoverBottomLeft();
	UFUNCTION()
	void OnMouseUnhoverBottomRight();
	UFUNCTION()
	void OnMouseUnhoverTopEdge();
	UFUNCTION()
	void OnMouseUnhoverTopLeft();
	UFUNCTION()
	void OnMouseUnhoverTopRight();
	UFUNCTION()
	void OnMouseUnhoverLeftEdge();
	UFUNCTION()
	void OnMouseUnhoverRightEdge();

	
	virtual void NativeConstruct() override;


};
