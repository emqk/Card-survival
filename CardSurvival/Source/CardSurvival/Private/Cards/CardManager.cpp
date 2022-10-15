// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardManager.h"
#include "Cards/Card.h"
#include "Cards/CardDummy.h"
#include "Player/PlayerSubsystem.h"
#include "Board/Board.h"
#include "Board/PlayZoneComponent.h"
#include "Interaction/InteractionAim.h"

ACardManager::ACardManager()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
}

void ACardManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UPlayerSubsystem>()->SetCardManager(this);

	// Spawn dummy card
	if (CardDummyClass)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform Transform;
		CardDummyInstance = Cast<ACardDummy>(GetWorld()->SpawnActor(CardDummyClass, &Transform, Params));
		DisableCardDummy();
	}
}

bool ACardManager::SpawnCardInRow(EBoardRow BoardRow, UCardData* CardData)
{
	UPlayZoneComponent* PlayZone = GetBoardRowFromEnum(BoardRow);
	if (PlayZone)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform Transform;

		ACard* SpawnedCard = Cast<ACard>(GetWorld()->SpawnActor(CardClass, &Transform, Params));
		SpawnedCard->SetCardData(CardData);
		PlayZone->AddCard(SpawnedCard);

		return true;
	}

	return false;
}

void ACardManager::DestroyAllCardsInRow(EBoardRow BoardRow)
{
	UPlayZoneComponent* PlayZone = GetBoardRowFromEnum(BoardRow);
	if (PlayZone)
	{
		PlayZone->DestroyAllCards();
	}
}

ACardDummy* ACardManager::EnableCardDummy()
{
	CardDummyInstance->SetActorHiddenInGame(false);
	return CardDummyInstance;
}

void ACardManager::DisableCardDummy()
{
	CardDummyInstance->SetActorHiddenInGame(true);
}

UPlayZoneComponent* ACardManager::GetBoardRowFromEnum(EBoardRow BoardRow) const
{
	UPlayerSubsystem* Subsystem = GetWorld()->GetSubsystem<UPlayerSubsystem>();
	ABoard* Board = Subsystem->GetBoard();

	if (Subsystem && Board)
	{
		switch (BoardRow)
		{
			case EBoardRow::EQ:					return Board->GetEQZone();
			case EBoardRow::PlayerInventory:	return Board->GetInventoryZone();
			case EBoardRow::Location:			return Board->GetLocationZone();
			default: return nullptr;
		}
	}

	return nullptr;
}
