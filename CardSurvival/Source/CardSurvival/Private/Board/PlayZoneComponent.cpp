// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/PlayZoneComponent.h"
#include "Utils/FollowComponent.h"
#include "Cards/Card.h"

UPlayZoneComponent::UPlayZoneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	BoxExtent = FVector(100, 100, 100);
}

bool UPlayZoneComponent::AddCard(TObjectPtr<ACardBase> CardToAdd, int32 Index /*= INDEX_NONE*/)
{
	if (Cards.Contains(CardToAdd))
	{
		UE_LOG(LogTemp, Error, TEXT("Card add the card - The card is already in this PlayZone!"));
		return false;
	}

	if (UPlayZoneComponent* CurrentZone = CardToAdd->GetPlayZone())
	{
		CurrentZone->RemoveCard(CardToAdd);
	}

	UFollowComponent* FollowComponent = CardToAdd->GetFollowComponent();
	FVector TargetLocation = GetCardLocationAtIndex(Cards.Num());
	FollowComponent->SetFollow(nullptr, TargetLocation, FRotator());

	CardToAdd->SetPlayZone(this);
	if (Cards.IsValidIndex(Index))
	{
		Cards.Insert({ CardToAdd }, Index);
	}
	else
	{
		Cards.Add(CardToAdd);
	}
	RefreshCardsLocation();

	return true;
}

bool UPlayZoneComponent::RemoveCard(TObjectPtr<ACardBase> CardToRemove)
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

void UPlayZoneComponent::MoveCardToIndex(ACardBase* CardToMove, int32 NewIndex)
{
	int32 CurrentIndex = Cards.IndexOfByKey(CardToMove);
	if (CurrentIndex == INDEX_NONE)
	{
		return;
	}

	if (NewIndex > Cards.Num() - 1)
	{
		NewIndex = Cards.Num() - 1;
	}

	if (CurrentIndex == NewIndex)
	{
		return;
	}

	if (CurrentIndex != INDEX_NONE)
	{
		Swap(Cards[CurrentIndex], Cards[NewIndex]);
		RefreshCardsLocation();
	}
}

void UPlayZoneComponent::DestroyAllCards()
{
	for (ACardBase* CurrentCard : Cards)
	{
		CurrentCard->Destroy();
	}

	Cards.Empty();
}

int32 UPlayZoneComponent::GetCardIndex(ACardBase* Card) const
{
	return Cards.IndexOfByKey(Card);
}

int32 UPlayZoneComponent::GetCardIndexFromLocation(const FVector& GlobalLocation)
{
	FVector ComponentLocation = GetComponentLocation();
	float StartY = (ComponentLocation.Y - GetComponentScale().Y * 100.0f) + DefaultOffsetY;
	float DifferenceY = GlobalLocation.Y - StartY;
	int32 Result = (DifferenceY) / (SpacingY);

	UE_LOG(LogTemp, Warning, TEXT("diffY %f, result %i"), DifferenceY, Result)

	return Result;
}

bool UPlayZoneComponent::IsLocationInPlayZone(const FVector2D& Location2D)
{
	FVector ComponentLocation = GetComponentLocation();
	FVector ComponentScale = GetComponentScale() * 100.0f;

	float StartX = ComponentLocation.X - ComponentScale.X;
	float EndX = ComponentLocation.X + ComponentScale.X;
	float StartY = ComponentLocation.Y - ComponentScale.Y;
	float EndY = ComponentLocation.Y + ComponentScale.Y;

	if (Location2D.X >= StartX && Location2D.X <= EndX
	&&	Location2D.Y >= StartY && Location2D.Y <= EndY)
	{
		return true;
	}

	return false;
}

FVector UPlayZoneComponent::GetCardLocationAtIndex(int Index)
{
	FVector ComponentLocation = GetComponentLocation();
	float StartOffsetX = (NumberOfRows - 1) * (SpacingX / 2.0f); // Start from the top
	float StartOffsetY = -GetComponentScale().Y * 100.0f + SpacingY / 2.0f; // Start from the left

	FVector Result = FVector(ComponentLocation.X - (Index % NumberOfRows) * SpacingX + StartOffsetX, ComponentLocation.Y + (Index / NumberOfRows) * SpacingY + StartOffsetY + DefaultOffsetY, ComponentLocation.Z + OffsetZ);
	
	return Result;
}

void UPlayZoneComponent::RefreshCardsLocation()
{
	for (int i = 0; i < Cards.Num(); i++)
	{
		ACardBase* Card = Cards[i];
		UFollowComponent* FollowComponent = Card->GetFollowComponent();
		FVector TargetLocation = GetCardLocationAtIndex(i);
		FollowComponent->SetFollow(nullptr, TargetLocation, FRotator());
	}
}

