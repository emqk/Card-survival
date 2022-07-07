// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapManager.h"
#include "WorldMap/MapNode.h"

AMapManager::AMapManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
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

FVector AMapManager::FindLevelLocationByIndex(int32 LevelIndex)
{
	return FVector(0 , LevelSize.Y * LevelIndex + (LevelSize.Y / 2.0f), 0) + MapLevelStartLocation;
}
