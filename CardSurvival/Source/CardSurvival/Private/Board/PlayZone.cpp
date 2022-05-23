// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/PlayZone.h"
#include "Utils/FollowComponent.h"
#include "Cards/Card.h"

APlayZone::APlayZone()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);
}

bool APlayZone::AddCard(ACard* CardToAdd)
{
	if (Cards.Contains(CardToAdd))
	{
		UE_LOG(LogTemp, Error, TEXT("Card add the card - The card is already in this PlayZone!"));
		return false;
	}

	UFollowComponent* FollowComponent = CardToAdd->GetFollowComponent();
	FVector TargetLocation = GetCardLocationAtIndex(Cards.Num());
	FollowComponent->SetFollow(nullptr, TargetLocation);

	CardToAdd->SetPlayZone(this);
	Cards.Add(CardToAdd);

	return true;
}

bool APlayZone::RemoveCard(ACard* CardToRemove)
{
	int32 NumOfRemovedCards = Cards.Remove(CardToRemove);

	if (NumOfRemovedCards > 0)
	{
		CardToRemove->SetPlayZone(nullptr);
		RefreshCardsLocation();
		return true;
	}
	else
	{
		return false;
	}
}

FVector APlayZone::GetCardLocationAtIndex(int Index)
{
	FVector ActorLocation = GetActorLocation();
	float StartOffsetX = (NumberOfRows - 1) * (SpacingX / 2.0f); // Start from the top
	float StartOffsetY = -GetActorScale().Y * 100.0f + SpacingY / 2.0f; // Start from the left

	FVector Result = FVector(ActorLocation.X - (Index % NumberOfRows) * SpacingX + StartOffsetX, ActorLocation.Y + (Index / NumberOfRows) * SpacingY + StartOffsetY, ActorLocation.Z + OffsetZ);
	
	return Result;
}

void APlayZone::RefreshCardsLocation()
{
	for (int i = 0; i < Cards.Num(); i++)
	{
		ACard* Card = Cards[i];
		UFollowComponent* FollowComponent = Card->GetFollowComponent();
		FVector TargetLocation = GetCardLocationAtIndex(i);
		FollowComponent->SetFollow(nullptr, TargetLocation);
	}
}
