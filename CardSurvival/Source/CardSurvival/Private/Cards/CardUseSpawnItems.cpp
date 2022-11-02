// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardUseSpawnItems.h"
#include "Cards/CardManager.h"
#include "Cards/CardBase.h"
#include "Board/PlayZoneComponent.h"
#include "Player/PlayerSubsystem.h"
#include "Kismet/KismetMathLibrary.h"

void UCardUseSpawnItems::Use_Implementation(ACardBase* From, ACardBase* To)
{
	UPlayZoneComponent* Zone = To->GetPlayZone();

	if (!Zone)
	{
		return;
	}

	Super::Use_Implementation(From, To);

	UWorld* Wo = From->GetWorld();
	UPlayerSubsystem* PlayerSubsystem = Wo->GetSubsystem<UPlayerSubsystem>();
	ACardManager* CardManager = PlayerSubsystem->GetCardManager();

	for (const FCardSpawnData& Data : CardsToSpawn)
	{
		int Amount = UKismetMathLibrary::RandomIntegerInRange(Data.AmountRange.X, Data.AmountRange.Y);
		for (int i = 0; i < Amount; i++)
		{
			CardManager->SpawnCardInRow(Zone, Data.CardData);
		}
	}
}
