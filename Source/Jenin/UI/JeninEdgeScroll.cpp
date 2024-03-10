// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninEdgeScroll.h"

#include "Components/WidgetInteractionComponent.h"
#include "Jenin/Player/JeninCameraPawn.h"

void UJeninEdgeScroll::NativeConstruct()
{
	Super::NativeConstruct();
	BottomEdge->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverBottomEdge);
	BottomLeft->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverBottomLeft);
	BottomRight->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverBottomRight);
	TopEdge->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverTopEdge);
	TopLeft->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverTopLeft);
	TopRight->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverTopRight);
	LeftEdge->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverLeftEdge);
	RightEdge->OnHovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseHoverRightEdge);
	
	BottomEdge->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverBottomEdge);
	BottomLeft->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverBottomLeft);
	BottomRight->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverBottomRight);
	TopEdge->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverTopEdge);
	TopLeft->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverTopLeft);
	TopRight->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverTopRight);
	LeftEdge->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverLeftEdge);
	RightEdge->OnUnhovered.AddDynamic(this, &UJeninEdgeScroll::OnMouseUnhoverRightEdge);
}

void UJeninEdgeScroll::OnMouseHoverBottomEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverBottomEdge = true;
}

void UJeninEdgeScroll::OnMouseHoverBottomLeft()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverBottomLeft = true;
	UE_LOG(LogTemp, Warning, TEXT("OnMouseHoverBottomLeft"));
}

void UJeninEdgeScroll::OnMouseHoverBottomRight()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverBottomRight = true;
}

void UJeninEdgeScroll::OnMouseHoverTopEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverTopEdge = true;
}

void UJeninEdgeScroll::OnMouseHoverTopLeft()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverTopLeft = true;
}

void UJeninEdgeScroll::OnMouseHoverTopRight()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverTopRight = true;
}

void UJeninEdgeScroll::OnMouseHoverLeftEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverLeftEdge = true;
}

void UJeninEdgeScroll::OnMouseHoverRightEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverRightEdge = true;
}

void UJeninEdgeScroll::OnMouseUnhoverBottomEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverBottomEdge = false;
}

void UJeninEdgeScroll::OnMouseUnhoverBottomLeft()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverBottomLeft = false;
}

void UJeninEdgeScroll::OnMouseUnhoverBottomRight()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverBottomRight = false;
}

void UJeninEdgeScroll::OnMouseUnhoverTopEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverTopEdge = false;
}

void UJeninEdgeScroll::OnMouseUnhoverTopLeft()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverTopLeft = false;
}

void UJeninEdgeScroll::OnMouseUnhoverTopRight()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverTopRight = false;
}

void UJeninEdgeScroll::OnMouseUnhoverLeftEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverLeftEdge = false;
}

void UJeninEdgeScroll::OnMouseUnhoverRightEdge()
{
	AJeninCameraPawn* JeninCameraPawn = Cast<AJeninCameraPawn>(GetOwningPlayerPawn());
	JeninCameraPawn->IsOverRightEdge = false;
}


