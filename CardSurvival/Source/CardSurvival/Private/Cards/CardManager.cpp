// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardManager.h"
#include "Cards/Card.h"
#include "Player/PlayerSubsystem.h"
#include "Board/Board.h"
#include "Board/PlayZoneComponent.h"

ACardManager::ACardManager()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
}

void ACardManager::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->SetCardManager(this);
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

UPlayZoneComponent* ACardManager::GetBoardRowFromEnum(EBoardRow BoardRow) const
{
	UPlayerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
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
