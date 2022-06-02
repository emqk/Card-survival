// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapManager.h"
#include "WorldMap/MapNode.h"

AMapManager::AMapManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AMapManager::CreateNewLevel()
{
	int32 NewLevelIndex = Levels.Num();
	FVector NewLevelLocation = FindLevelLocationByIndex(NewLevelIndex);
	float HalfNodeSize = NodeSize / 2.0f;

	FMapLevelData NewLevelData;

	int32 NumOfNewNodes = FMath::RandRange(NodesInLevelRange.X, NodesInLevelRange.Y);
	float Split = LevelSize.X / NumOfNewNodes;
	for (int32 i = 0; i < NumOfNewNodes; i++)
	{
		float HalfLevelSizeY = LevelSize.Y / 2.0f;
		float X = FMath::RandRange(HalfNodeSize, Split - HalfNodeSize) + Split * i;
		float Y = FMath::RandRange(-HalfLevelSizeY + HalfNodeSize, HalfLevelSizeY - HalfNodeSize);
		FVector SpawnLocation = FVector(X, Y, 0) + NewLevelLocation;

		AMapNode* NewNode = SpawnNode(SpawnLocation);
		NewLevelData.Nodes.Add(NewNode);
	}

	Levels.Add(NewLevelData);
}

AMapNode* AMapManager::SpawnNode(const FVector& Location)
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Transform;
	Transform.SetLocation(Location);

	AMapNode* Instance = Cast<AMapNode>(GetWorld()->SpawnActor(MapNodeClass, &Transform, Params));

	return Instance;
}

void AMapManager::ConnectNodesInLevel(int32 LevelIndex)
{
	if (LevelIndex + 1 < Levels.Num())
	{
		FMapLevelData& CurrentLevel = Levels[LevelIndex];
		FMapLevelData& NextLevel = Levels[LevelIndex + 1];

		for (AMapNode* CurrentNode : CurrentLevel.Nodes)
		{
			for (AMapNode* NextNode : NextLevel.Nodes)
			{
				CurrentNode->AddConnection(NextNode);
			}
		}
	}
}

FVector AMapManager::FindLevelLocationByIndex(int32 LevelIndex)
{
	return FVector(0 , LevelSize.Y * LevelIndex + (LevelSize.Y / 2.0f), 0) + MapLevelStartLocation;
}
