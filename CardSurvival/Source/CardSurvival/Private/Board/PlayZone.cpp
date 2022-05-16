// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/PlayZone.h"
#include "Utils/FollowComponent.h"
#include "Card.h"

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
	FollowComponent->SetFollow(nullptr, GetActorLocation() + FVector(0, 0, 100));

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
		return true;
	}
	else
	{
		return false;
	}
}

