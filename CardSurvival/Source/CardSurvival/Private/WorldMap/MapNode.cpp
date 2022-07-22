// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapNode.h"
#include "Player/PlayerMapPawn.h"
#include "Player/PlayerSubsystem.h"
#include "Player/PlayerBoardPawn.h"
#include "WorldMap/MapManager.h"
#include "WorldMap/MapNodeData.h"
#include "Board/LevelStreamingSubsystem.h"
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

			// Go to the board and load the map /// Need to clean this up :) 
			/// Remember to destroy old enviro!
			if (NodeData->GetEnvironmentData())
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				APlayerBoardPawn* PlayerBoardPawn = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerBoardPawn();
				PlayerController->Possess(PlayerBoardPawn);

				UEnvironmentData* EnvironmentData = NodeData->GetEnvironmentData();
				GetGameInstance()->GetSubsystem<ULevelStreamingSubsystem>()->LoadLevelInstance(EnvironmentData->GetLevelInstance(), EnvironmentData->GetOffset());
			}
		}

		return true;
	}

	return false;
}
