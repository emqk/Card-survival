// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapNode.h"
#include "Player/PlayerSubsystem.h"
#include "Player/PlayerMapPawn.h"
#include "WorldMap/MapManager.h"
#include "WorldMap/MapNodeData.h"
#include "World/WorldLoaderSubsystem.h"
#include "Events/EventsManager.h"

AMapNode::AMapNode()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

UEventData* AMapNode::GetRandomEventData() const
{
	if (EventDatas.Num() <= 0)
	{
		return nullptr;
	}
	
	int32 Index = FMath::RandRange(0, EventDatas.Num() - 1);
	return EventDatas[Index];
}

bool AMapNode::StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType)
{
	if (InteractionType == EInteractionType::Primary)
	{
		UPlayerSubsystem* PlayerSubsystem = GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
		AMapManager* MapManager = PlayerSubsystem->GetMapManager();

		APlayerMapPawn* PlayerPawn = PlayerSubsystem->GetPlayerMapPawn();
		FIntPoint NewMapIndex = MapManager->ConvertWorldLocationToMapIndex(GetActorLocation());
		UMapNodeData* NodeData = MapManager->GetDataGlobalXY(NewMapIndex.X, NewMapIndex.Y);

		if (MapManager->IsNodeWalkable(NewMapIndex) && NewMapIndex.Y >= PlayerPawn->GetWorldIndex().Y)
		{
			PlayerPawn->MoveToWorldIndex(NewMapIndex);

			UEventData* EventToStart = GetRandomEventData();
			if (EventToStart)
			{
				PlayerSubsystem->GetEventsManager()->StartEvent(EventToStart);
			}

		
			// Go to the board
			UEnvironmentData* EnvironmentData = NodeData->GetEnvironmentData();
			UWorldLoaderSubsystem* WorldLoader = GetGameInstance()->GetSubsystem<UWorldLoaderSubsystem>();
			if (EnvironmentData && WorldLoader)
			{
				WorldLoader->OpenNewEnvironment(EnvironmentData);
				return true;
			}
		}
	}

	return false;
}
