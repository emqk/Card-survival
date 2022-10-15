// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapManager.h"
#include "WorldMap/MapNode.h"
#include "WorldMap/MapNodeData.h"
#include "Player/PlayerMapPawn.h"
#include "Player/PlayerSubsystem.h"

AMapManager::AMapManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AMapManager::BeginPlay()
{
	Super::BeginPlay();

	// Register map manager
	GetWorld()->GetSubsystem<UPlayerSubsystem>()->SetMapManager(this);

	// Generate world
	for (int i = 0; i < NumberOfStagesToGenerate; i++)
	{
		GenerateNextStage();
	}

	// Spawn Player
	if (MapStages.Num() > 0)
	{
		FTransform SpawnTransform;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlayerMapPawn = Cast<APlayerMapPawn>(GetWorld()->SpawnActor(PlayerMapPawnClass, &SpawnTransform, SpawnParams));
		FIntPoint WorldIndex = MapStages[0]->GetPOIs()[0];

		PlayerMapPawn->MoveToWorldIndex_Instant(WorldIndex);
	}

	// Debug
	if (bDebugShowAllNodes)
	{
		SpawnAllNodes();
	}
}

void AMapManager::GenerateNextStage()
{
	UMapStageData* NewData = NewObject<UMapStageData>(this);
	NewData->Generate(StageSize.X, StageSize.Y, MapStages.Num(), ForestNodeData);
	MapStages.Add(NewData);

	// POI
	int32 NumOfNewNodes = FMath::RandRange(NodesInStageRange.X, NodesInStageRange.Y);
	int Split = StageSize.X / NumOfNewNodes;
	FIntPoint IndexRangeYFromTo(POILocalYMargin, StageSize.Y - 1 - POILocalYMargin);
	for (int32 i = 0; i < NumOfNewNodes; i++)
	{
		float X = FMath::RandRange(POILocalXMargin, Split - 1 - POILocalXMargin) + Split * i;
		float Y = FMath::RandRange(IndexRangeYFromTo.X, IndexRangeYFromTo.Y);

		// Add random POI
		UMapNodeData* MapNodeData = POIsData[FMath::RandRange(0, POIsData.Num() - 1)];
		NewData->AddPOI(X, Y, MapNodeData);
	}

	// Connection
	ConnectWithNextStage(MapStages.Num() - 2);
}

void AMapManager::SpawnAllNodes()
{
	for (int X = 0; X < StageSize.X; X++)
	{
		for (int Y = 0; Y < StageSize.Y * MapStages.Num(); Y++)
		{
			SpawnNodeAtIndex(FIntPoint(X, Y));
		}
	}
}

void AMapManager::SpawnNodesInView(const FIntPoint& WorldIndex, int32 View)
{
	// Spawn nodes
	TArray<FIntPoint> Indices;
	FindNodeIndicesInView(WorldIndex, View, Indices);
	for (const FIntPoint& Index : Indices)
	{
		SpawnNodeAtIndex(Index);
	}

	// Remove out of view
	TArray<FIntPoint> SpawnedIndices;
	SpawnedNodes.GetKeys(SpawnedIndices);
	for (const FIntPoint& Index : SpawnedIndices)
	{
		if (!Indices.Contains(Index))
		{
			SpawnedNodes[Index]->Destroy();
			SpawnedNodes.Remove(Index);
		}
	}
}

FVector AMapManager::GetWorldLocationFromIndex(const FIntPoint& WorldIndex) const
{
	return FVector(WorldIndex.X * NodeOffset.X + (WorldIndex.Y % 2 == 0 ? NodeOffset.X / 2.0f : 0), WorldIndex.Y * NodeOffset.Y, 0) + MapStartLocation;
}

FIntPoint AMapManager::ConvertWorldLocationToMapIndex(const FVector& WorldLocation) const
{
	FVector Temp = (WorldLocation - MapStartLocation);
	Temp.X /= NodeOffset.X;
	Temp.Y /= NodeOffset.Y;

	return FIntPoint(Temp.X, Temp.Y);
}

bool AMapManager::IsNodeWalkable(const FIntPoint& WorldIndex) const
{
	UMapNodeData* Data = GetDataGlobalXY(WorldIndex.X, WorldIndex.Y);
	return Data->GetIsWalkable();
}

AMapNode* AMapManager::SpawnNodeAtIndexFromData(const FIntPoint& WorldIndex, const TSubclassOf<AMapNode>& ClassToSpawn)
{
	if (IsNodeAtIndex(WorldIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't spawn map node! - Already in the location"))
		return nullptr;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector WorldLocation = FindWorldLocationFromIndex(WorldIndex);
	FTransform Transform;
	Transform.SetLocation(WorldLocation);

	AMapNode* Instance = Cast<AMapNode>(GetWorld()->SpawnActor(ClassToSpawn, &Transform, Params));
	SpawnedNodes.Add(WorldIndex, Instance);

	return Instance;
}

AMapNode* AMapManager::SpawnNodeAtIndex(const FIntPoint& WorldIndex)
{
	UMapNodeData* NodeData = GetDataGlobalXY(WorldIndex.X, WorldIndex.Y);
	TSubclassOf<AMapNode> ToSpawn = NodeData->GetNodeClass();

	return SpawnNodeAtIndexFromData(WorldIndex, ToSpawn);
}

AMapNode* AMapManager::GetNodeAtIndex(const FIntPoint& WorldIndex) const
{
	if (!IsNodeAtIndex(WorldIndex))
	{
		return nullptr;
	}

	return SpawnedNodes[WorldIndex];
}

bool AMapManager::IsNodeAtIndex(const FIntPoint& WorldIndex) const
{
	return SpawnedNodes.Contains(WorldIndex);
}

void AMapManager::FindNodeIndicesInView(const FIntPoint& Origin, int32 View, TArray<FIntPoint>& OutIndices) const
{
	if (View < 0)
	{
		return;
	}

	// Get data of the current node
	UMapNodeData* NodeData = GetDataGlobalXY(Origin.X, Origin.Y);
	if (!NodeData)
	{
		return;
	}

	// Is this node still visible after applying visibility cost?
	if (View >= 0)
	{
		OutIndices.AddUnique(Origin);
	}
	else
	{
		return;
	}

	// Apply visibility cost
	View -= NodeData->GetVisibility();

	// Check neighbours
	TArray<FIntPoint> Neighbours = GetNeighbours(Origin);
	for (const FIntPoint& NeighbourIndex : Neighbours)
	{
		FindNodeIndicesInView(NeighbourIndex, View, OutIndices);
	}
}

int32 AMapManager::FindStageIndexByIndex(const FIntPoint& WorldIndex) const
{
	return WorldIndex.Y / StageSize.Y;
}

FVector AMapManager::FindStageLocationByIndex(int32 StageIndex) const
{
	FVector2D StageSizeWorld = FVector2D(StageSize.X * 100, StageSize.Y * 100);
	return FVector(0 , StageSizeWorld.Y * StageIndex + (StageSizeWorld.Y / 2.0f), 0) + MapStartLocation;
}

FVector AMapManager::FindWorldLocationFromIndex(const FIntPoint& WorldIndex) const
{
	int32 StageIndex = FindStageIndexByIndex(WorldIndex);
	return MapStartLocation + FVector(WorldIndex.X * NodeOffset.X + (WorldIndex.Y % 2 == 0 ? NodeOffset.X / 2.0f : 0), WorldIndex.Y * NodeOffset.Y, 0);
}

FIntPoint AMapManager::GetGlobalMapStageOffset(const UMapStageData* MapStage) const
{
	int CurrentStage = MapStage->GetStage();
	return FIntPoint(0, CurrentStage * StageSize.Y);
}

FIntPoint AMapManager::GetGlobalXY(const UMapStageData* MapStage, int LocalX, int LocalY) const
{
	FIntPoint CurrentStageOffset = GetGlobalMapStageOffset(MapStage);
	return FIntPoint(CurrentStageOffset.X + LocalX, CurrentStageOffset.Y + LocalY);
}

bool AMapManager::SetDataGlobalXY(int GlobalX, int GlobalY, UMapNodeData* Value)
{		
	int Index = GlobalY / StageSize.Y;
	bool Found = MapStages.IsValidIndex(Index);
	if (!Found)
	{
		return false;
	}

	int LocalY = GlobalY % StageSize.Y;
	MapStages[Index]->SetDataAt(GlobalX, LocalY, Value);
	return true;
}

TArray<FIntPoint> AMapManager::GetNeighbours(const FIntPoint& Center) const
{
	TArray<FIntPoint> Result;

	Result.Add(Center + FIntPoint(1, 0));
	Result.Add(Center + FIntPoint(-1, 0));
	Result.Add(Center + FIntPoint(0, 1));
	Result.Add(Center + FIntPoint(0, -1));

	if (Center.Y % 2 == 0)
	{
		Result.Add(Center + FIntPoint(1, 1));
		Result.Add(Center + FIntPoint(1, -1));
	}
	else
	{
		Result.Add(Center + FIntPoint(-1, 1));
		Result.Add(Center + FIntPoint(-1, -1));
	}

	return Result;
}

FIntPoint AMapManager::FindClosestNeighbour(const TArray<FIntPoint>& Neighbours, const FIntPoint& Destination) const
{
	float Closest = TNumericLimits<float>::Max();
	FIntPoint Result;

	for (const FIntPoint& Curr : Neighbours)
	{
		float DistanceSq = FVector2D::DistSquared(Curr, Destination);
		if (DistanceSq < Closest)
		{
			Result = Curr;
			Closest = DistanceSq;
		}
	}

	return Result;
}

void AMapManager::ConnectWithNextStage(int StageIndex)
{
	if (!MapStages.IsValidIndex(StageIndex) || !MapStages.IsValidIndex(StageIndex + 1))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't connect with next stage - Index out of range!"))
		return;
	}

	UMapStageData* LeftMapStage = MapStages[StageIndex];
	TArray<FIntPoint> LeftPOIs = LeftMapStage->GetPOIs();

	UMapStageData* RightMapStage = MapStages[StageIndex + 1];
	TArray<FIntPoint> RightPOIs = RightMapStage->GetPOIs();

	for (const FIntPoint& LeftPOI : LeftPOIs)
	{
		FIntPoint LeftPOIGlobal = GetGlobalXY(LeftMapStage, LeftPOI.X, LeftPOI.Y);

		for (const FIntPoint& RightPOI : RightPOIs)
		{
			FIntPoint RightPOIGlobal = GetGlobalXY(RightMapStage, RightPOI.X, RightPOI.Y);
			CreateRoadFromTo(LeftPOIGlobal + FIntPoint(0, 1), RightPOIGlobal);
		}
	}
}

void AMapManager::CreateRoadFromTo(const FIntPoint& From, const FIntPoint& To)
{
	FIntPoint RoadIndex = From;
	while (RoadIndex != To)
	{
		SetDataGlobalXY(RoadIndex.X, RoadIndex.Y, RoadNodeData);

		TArray<FIntPoint> Neighbours = GetNeighbours(RoadIndex);
		FIntPoint Closest = FindClosestNeighbour(Neighbours, To);

		RoadIndex = Closest;
	}
}

UMapNodeData* AMapManager::GetDataGlobalXY(int GlobalX, int GlobalY) const
{
	int Index = GlobalY / StageSize.Y;
	bool Found = MapStages.IsValidIndex(Index);
	if (!Found)
	{
		return nullptr;
	}

	int LocalY = GlobalY % StageSize.Y;
	UMapNodeData* Data = MapStages[Index]->GetDataAt(GlobalX, LocalY);

	return Data;
}

bool AMapManager::IsThisLastPOIIndex(const FIntPoint& WorldIndex) const
{
	UMapNodeData* Data = GetDataGlobalXY(WorldIndex.X, WorldIndex.Y);
	if (!Data->GetEnvironmentData())
	{
		return false;
	}

	int32 Index = FindStageIndexByIndex(WorldIndex);
	if (Index >= MapStages.Num() - 1)
	{
		return true;
	}

	return false;
}
