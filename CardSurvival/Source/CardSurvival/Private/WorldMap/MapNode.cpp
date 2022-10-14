// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapNode.h"
#include "Player/PlayerSubsystem.h"
#include "Player/PlayerMapPawn.h"
#include "Player/PlayerInventorySubsystem.h"
#include "WorldMap/MapManager.h"
#include "WorldMap/MapNodeData.h"
#include "World/WorldLoaderSubsystem.h"
#include "Events/EventsManager.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Statistic.h"

AMapNode::AMapNode()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

bool AMapNode::StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType)
{
	if (InteractionType == EInteractionType::Primary)
	{
		UPlayerSubsystem* PlayerSubsystem = GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
		UPlayerInventorySubsystem* PlayerInventory = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
		AMapManager* MapManager = PlayerSubsystem->GetMapManager();

		APlayerMapPawn* PlayerPawn = PlayerSubsystem->GetPlayerMapPawn();
		FIntPoint NewMapIndex = MapManager->ConvertWorldLocationToMapIndex(GetActorLocation());
		UMapNodeData* NodeData = MapManager->GetDataGlobalXY(NewMapIndex.X, NewMapIndex.Y);

		if (MapManager->IsNodeWalkable(NewMapIndex) && NewMapIndex.Y >= PlayerPawn->GetWorldIndex().Y)
		{
			PlayerPawn->MoveToWorldIndex(NewMapIndex);
		
			UGameplayStatics::PlaySound2D(GetWorld(), WalkSound);

			//Stats
			int32 EnergyCost = PlayerPawn->GetEnergyDecreaseAfterStep();
			PlayerInventory->GetEnergy()->ChangeByAmount(EnergyCost);
			PlayerPawn->RefreshStats();

			// Go to the board
			UEnvironmentData* EnvironmentData = NodeData->GetEnvironmentData();
			UWorldLoaderSubsystem* WorldLoader = GetGameInstance()->GetSubsystem<UWorldLoaderSubsystem>();
			if (EnvironmentData && WorldLoader)
			{
				WorldLoader->OpenNewEnvironment(EnvironmentData);
				return true;
			}

			// Try start an event
			if (!EnvironmentData)
			{
				PlayerSubsystem->GetEventsManager()->TryStartRandomEvent();
			}
		}
	}

	return false;
}
