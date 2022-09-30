// Fill out your copyright notice in the Description page of Project Settings.


#include "World/WorldLoaderSubsystem.h"
#include "World/SmartPostProcessVolume.h"
#include "WorldMap/MapLighting.h"
#include "Board/LevelStreamingSubsystem.h"
#include "Board/EnvironmentData.h"
#include "Tokens/TokenRow.h"
#include "Cards/CardManager.h"
#include "Player/PlayerMapPawn.h"
#include "Player/PlayerSubsystem.h"
#include "Player/PlayerBoardPawn.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UWorldLoaderSubsystem::OpenNewEnvironment(UEnvironmentData* EnvironmentData)
{
	UPlayerSubsystem* PlayerSubsystem = GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
	
	// Possess the board player and load the environment
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerBoardPawn* PlayerBoardPawn = PlayerSubsystem->GetPlayerBoardPawn();
	PlayerController->Possess(PlayerBoardPawn);

	GetGameInstance()->GetSubsystem<ULevelStreamingSubsystem>()->LoadLevelInstance(EnvironmentData->GetLevelInstance(), FVector(2350.0f, 0.0f, -80.0f));

	if (MapLighting && MapPostProcess)
	{
		MapLighting->Deactivate();
		MapPostProcess->bEnabled = false;
	}

	// Destroy old cards and spawn new ones
	ACardManager* CardManager = PlayerSubsystem->GetCardManager();
	CardManager->DestroyAllCardsInRow(EBoardRow::Location);

	const TArray<FCardSpawnData>& CardSpawnDatas = EnvironmentData->GetCardSpawnData();
	for (const FCardSpawnData& SpawnData : CardSpawnDatas)
	{
		int Amount = UKismetMathLibrary::RandomIntegerInRange(SpawnData.AmountRange.X, SpawnData.AmountRange.Y);
		for (int i = 0; i < Amount; i++)
		{
			CardManager->SpawnCardInRow(EBoardRow::Location, SpawnData.CardData);
		}
	}

	// Apply token effects
	ATokenRow* TokenRow = PlayerSubsystem->GetTokenRow();
	if (TokenRow)
	{
		TokenRow->ApplyAllTokensEffects();
	}
}

void UWorldLoaderSubsystem::OpenMap()
{
	// Possess the map player
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerMapPawn* PlayerPawn = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerMapPawn();

	PlayerController->Possess(PlayerPawn);

	// Lighting setup
	if (MapLighting && MapPostProcess)
	{
		MapLighting->Activate();
		MapPostProcess->bEnabled = true;
	}
}
