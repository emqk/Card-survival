// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapSubsystem.h"
#include "WorldMap/MapNode.h"

void UMapSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("MapSubsystem initialized (C++)"))

	BlueprintInitialize();
}

void UMapSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UMapSubsystem::CreateNewLevel()
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

AMapNode* UMapSubsystem::SpawnNode(const FVector& Location)
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Transform;
	Transform.SetLocation(Location);

	AMapNode* Instance = Cast<AMapNode>(GetWorld()->SpawnActor(MapNodeClass, &Transform, Params));

	return Instance;
}

FVector UMapSubsystem::FindLevelLocationByIndex(int32 LevelIndex)
{
	return FVector(0 , LevelSize.Y * LevelIndex + (LevelSize.Y / 2.0f), 0) + MapLevelStartLocation;
}
