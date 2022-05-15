// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "Utils/FollowComponent.h"
#include "Player/PlayerSubsystem.h"
#include "Player/Cursor.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);
	NameTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameText"));
	NameTextComponent->SetupAttachment(BaseMeshComponent);

	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}

bool ACard::StartInteraction_Implementation(AActor* Interactor)
{		
	SetActorEnableCollision(false);

	ACursor* Cursor3D = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerCursor3D();
	FollowComponent->SetFollow(Cursor3D, HoldHeightOffset, false);

	return true;
}

bool ACard::TickInteraction_Implementation(AActor* Interactor)
{
	return true;
}

bool ACard::EndInteraction_Implementation(AActor* Interactor)
{
	SetActorEnableCollision(true);

	FVector CurrentLocation = GetActorLocation();
	FollowComponent->SetFollow(nullptr, FVector(CurrentLocation.X, CurrentLocation.Y, 0));

	return true;
}
