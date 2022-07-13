// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapManager.h"
#include "WorldMap/MapNode.h"
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
	FMapStageData NewData;
	NewData.Generate(StageSize.X, StageSize.Y, MapStages.Num());

	// POI
	int32 NumOfNewNodes = FMath::RandRange(NodesInStageRange.X, NodesInStageRange.Y);
	int Split = StageSize.X / NumOfNewNodes;
	FIntPoint IndexRangeYFromTo(POILocalYMargin, StageSize.Y - 1 - POILocalYMargin);
	for (int32 i = 0; i < NumOfNewNodes; i++)
	{
		float X = FMath::RandRange(POILocalXMargin, Split - 1 - POILocalXMargin) + Split * i;
		float Y = FMath::RandRange(IndexRangeYFromTo.X, IndexRangeYFromTo.Y);

		NewData.AddPOI(X, Y);
	}

	// Connections
	bool PreviousMapStageFound = MapStages.IsValidIndex(MapStages.Num() - 1);
	FMapStageData* PreviousMapStage = nullptr;
	if (PreviousMapStageFound)
	{
		PreviousMapStage = &MapStages[MapStages.Num() - 1];
	}

	MapStages.Add(NewData); // Must to add NewData to the array after setting PreviousMapStageFound, and before SetGlobalXY. Need to change FMapStageData from struct to class. This will allow to have an array of pointers, which would remove this weird execution order

	FIntPoint RightPOI = NewData.GetPOIs()[0];
	RightPOI = GetGlobalXY(NewData, RightPOI.X, RightPOI.Y);
	if (PreviousMapStageFound)
	{
		FIntPoint LeftPOI = PreviousMapStage->GetPOIs()[0];
		LeftPOI = GetGlobalXY(*PreviousMapStage, LeftPOI.X, LeftPOI.Y);
		int StartY = LeftPOI.Y + 1;
		int EndY = RightPOI.Y - 1;

		float CurrentX = LeftPOI.X;
		float CurrentY = (float)StartY;
		FVector2D Dir = FVector2D(RightPOI.X - LeftPOI.X, RightPOI.Y - LeftPOI.Y);
		Dir.Normalize();

		int LastX = -1;
		int LastY = -1;
		while (FMath::RoundToInt(CurrentY) <= EndY || FMath::RoundToInt(CurrentX) <= RightPOI.X - 1)
		{
			int X = FMath::RoundToInt(CurrentX);
			int Y = FMath::RoundToInt(CurrentY);

			SetDataGlobalXY(X, Y, 2);
			if (LastX != -1)
			{
				int DiffX = FMath::Abs(LastX - X);
				int DiffY = FMath::Abs(LastY - Y);
				int MoveSum =  DiffX + DiffY;
				if (MoveSum > 1)
				{
					int PreviousX = FMath::RoundToInt(CurrentX - Dir.X);
					int PreviousY = FMath::RoundToInt(CurrentY - Dir.Y);
					SetDataGlobalXY(PreviousX, Y, 2);
				}
			}

			CurrentX += Dir.X;
			CurrentY += Dir.Y;
			LastX = X;
			LastY = Y;
		}
	}

	// Player
	if (MapStages.Num() == 1)
	{
		FTransform SpawnTransform;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PlayerMapPawn = Cast<APlayerMapPawn>(GetWorld()->SpawnActor(PlayerMapPawnClass, &SpawnTransform, SpawnParams));
		FIntPoint WorldIndex = NewData.GetPOIs()[0];
		PlayerMapPawn->MoveToWorldIndex_Instant(WorldIndex);
	}
}

void AMapManager::SpawnNodes()
{
	int i = 0;
	for (FMapStageData& Stage : MapStages)
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
				int HexData = Stage.GetDataAt(X, Y);
				if (HexData == 0)
				{
					ToSpawn = EnviroNodeClass;
				}
				else if (HexData == 1)
				{
					ToSpawn = InteractableForestClass;
				}
				else if (HexData == 2)
				{
					ToSpawn = RoadNodeClass;
				}

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
	return GetDataGlobalXY(WorldIndex.X, WorldIndex.Y) == 2;
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

FIntPoint AMapManager::GetGlobalMapStageOffset(const FMapStageData& MapStage) const
{
	int CurrentStage = MapStage.GetStage();
	return FIntPoint(0, CurrentStage * StageSize.Y);
}

FIntPoint AMapManager::GetGlobalXY(const FMapStageData& MapStage, int LocalX, int LocalY) const
{
	FIntPoint CurrentStageOffset = GetGlobalMapStageOffset(MapStage);
	return FIntPoint(CurrentStageOffset.X + LocalX, CurrentStageOffset.Y + LocalY);
}

bool AMapManager::SetDataGlobalXY(int GlobalX, int GlobalY, int Value)
{		
	int Index = GlobalY / StageSize.Y;
	bool Found = MapStages.IsValidIndex(Index);
	if (!Found)
	{
		return false;
	}

	int LocalY = GlobalY % StageSize.Y;
	MapStages[Index].SetDataAt(GlobalX, LocalY, Value);
	return true;
}

int AMapManager::GetDataGlobalXY(int GlobalX, int GlobalY) const
{
	int Index = GlobalY / StageSize.Y;
	bool Found = MapStages.IsValidIndex(Index);
	if (!Found)
	{
		return -1;
	}

	int LocalY = GlobalY % StageSize.Y;
	int Data = MapStages[Index].GetDataAt(GlobalX, LocalY);

	return Data;
}
