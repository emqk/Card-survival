// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
#include "Components/TextRenderComponent.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);
	NameTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameText"));
	NameTextComponent->SetupAttachment(BaseMeshComponent);
}

bool ACard::StartInteraction_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("StartInteraction_Implementation"))
	return true;
}

bool ACard::TickInteraction_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("TickInteraction_Implementation"))
	
	FVector CurrentLocation = GetActorLocation();
	FVector NewActorLocation = FVector(CurrentLocation.X, CurrentLocation.Y, 200);

	SetActorLocation(NewActorLocation);

	return true;
}

bool ACard::EndInteraction_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("EndInteraction_Implementation"))


	FVector CurrentLocation = GetActorLocation();
	FVector NewActorLocation = FVector(CurrentLocation.X, CurrentLocation.Y, 0);
	SetActorLocation(NewActorLocation);


	return true;
}
