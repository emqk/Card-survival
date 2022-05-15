// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "Utils/FollowComponent.h"
#include "Player/PlayerSubsystem.h"

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
	SetActorEnableCollision(false);

	UFollowComponent* FollowComp = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerFollowComponent();
	FollowComp->SetFollower(this);

	return true;
}

bool ACard::TickInteraction_Implementation(AActor* Interactor)
{
	return true;
}

bool ACard::EndInteraction_Implementation(AActor* Interactor)
{
	SetActorEnableCollision(true);

	UFollowComponent* FollowComp = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerFollowComponent();
	FollowComp->SetFollower(nullptr);

	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, 0));

	return true;
}
