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
	GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->SetMapManager(this);

	// Generate world
	for (int i = 0; i < NumberOfStagesToGenerate; i++)
	{
		GenerateNextStage();
	}
	SpawnNodes();
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

		// Add (random POI)
		UMapNodeData* MapNodeData = FMath::RandRange(0, 1) == 0 ? InteractableForestData : InteractableGraveyardData;
		NewData->AddPOI(X, Y, MapNodeData);
	}

	// Connection
	ConnectWithNextStage(MapStages.Num() - 2);

	// Player
	if (MapStages.Num() == 1)
	{
		FTransform SpawnTransform;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PlayerMapPawn = Cast<APlayerMapPawn>(GetWorld()->SpawnActor(PlayerMapPawnClass, &SpawnTransform, SpawnParams));
		FIntPoint WorldIndex = NewData->GetPOIs()[0];
		PlayerMapPawn->MoveToWorldIndex_Instant(WorldIndex);
	}
}

void AMapManager::SpawnNodes()
{
	int i = 0;
	for (UMapStageData* Stage : MapStages)
	{
		for (int X = 0; X < StageSize.X; X++)
		{
			for (int Y = 0; Y < StageSize.Y; Y++)
			{
				FVector SpawnLocation =
					MapStartLocation
					+ FVector(X * NodeOffset.X + (Y % 2 == 0 ? NodeOffset.X / 2.0f : 0), Y * NodeOffset.Y, 0) /*+ FVector(0, 500 * i, 0)*/
					+ FVector(0, i * StageSize.Y * NodeOffset.Y, 0);

				TSubclassOf<AMapNode> ToSpawn;
				UMapNodeData* NodeData = Stage->GetDataAt(X, Y);
				ToSpawn = NodeData->GetNodeClass();

				SpawnNode(SpawnLocation, ToSpawn);
			}
		}

		i++;
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

AMapNode* AMapManager::SpawnNode(const FVector& Location, const TSubclassOf<AMapNode>& ClassToSpawn)
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Transform;
	Transform.SetLocation(Location);

	AMapNode* Instance = Cast<AMapNode>(GetWorld()->SpawnActor(ClassToSpawn, &Transform, Params));

	return Instance;
}

FVector AMapManager::FindStageLocationByIndex(int32 StageIndex)
{
	FVector2D StageSizeWorld = FVector2D(StageSize.X * 100, StageSize.Y * 100);
	return FVector(0 , StageSizeWorld.Y * StageIndex + (StageSizeWorld.Y / 2.0f), 0) + MapStartLocation;
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
	FIntPoint LeftPOI = LeftMapStage->GetPOIs()[0];
	LeftPOI = GetGlobalXY(LeftMapStage, LeftPOI.X, LeftPOI.Y);

	UMapStageData* RightMapStage = MapStages[StageIndex + 1];
	FIntPoint RightPOI = RightMapStage->GetPOIs()[0];
	RightPOI = GetGlobalXY(RightMapStage, RightPOI.X, RightPOI.Y);

	//Road
	CreateRoadFromTo(LeftPOI + FIntPoint(0, 1), RightPOI);
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
