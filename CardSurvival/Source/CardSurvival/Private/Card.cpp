// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "Utils/FollowComponent.h"
#include "Board/PlayZone.h"
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

	if (PlayZone)
	{
		PlayZone->RemoveCard(this);
	}

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

	// Add this Card to the PlayZone if available
	const FHitResult& HitResult = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetHitResultUnderCursor();
	AActor* HitActor = HitResult.GetActor();
	APlayZone* HitPlayZone = Cast<APlayZone>(HitActor);

	if (HitPlayZone)
	{
		HitPlayZone->AddCard(this);
	}
	else
	{
		FollowComponent->SetFollow(nullptr, FVector(CurrentLocation.X, CurrentLocation.Y, 0));
	}

	return true;
}
