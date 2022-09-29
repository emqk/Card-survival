// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldMap/MapStageData.h"
#include "MapManager.generated.h"

class APlayerMapPawn;
class AMapNode;
class UMapNodeData;

UCLASS()
class CARDSURVIVAL_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:

	AMapManager();

	// Overrides
	void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void GenerateNextStage();
	UFUNCTION(BlueprintCallable)
	void SpawnAllNodes();
	void SpawnNodesInView(const FIntPoint& WorldIndex, int32 View);

	FVector GetWorldLocationFromIndex(const FIntPoint& WorldIndex) const;
	FIntPoint ConvertWorldLocationToMapIndex(const FVector& WorldLocation) const;

	bool IsNodeWalkable(const FIntPoint& WorldIndex) const;
	UMapNodeData* GetDataGlobalXY(int GlobalX, int GlobalY) const;

protected:
	AMapNode* SpawnNodeAtIndexFromData(const FIntPoint& WorldIndex, const TSubclassOf<AMapNode>& ClassToSpawn);
	AMapNode* SpawnNodeAtIndex(const FIntPoint& WorldIndex);
	AMapNode* GetNodeAtIndex(const FIntPoint& WorldIndex) const;
	bool IsNodeAtIndex(const FIntPoint& WorldIndex) const;

	void FindNodeIndicesInView(const FIntPoint& Origin, int32 View, TArray<FIntPoint>& OutIndices) const;

	int32 FindStageIndexByIndex(const FIntPoint& WorldIndex) const;
	FVector FindStageLocationByIndex(int32 StageIndex) const;
	FVector FindWorldLocationFromIndex(const FIntPoint& WorldIndex) const;
	FIntPoint GetGlobalMapStageOffset(const UMapStageData* MapStage) const;
	FIntPoint GetGlobalXY(const UMapStageData* MapStage, int LocalX, int LocalY) const;
	bool SetDataGlobalXY(int GlobalX, int GlobalY, UMapNodeData* Value);
	TArray<FIntPoint> GetNeighbours(const FIntPoint& Center) const;
	FIntPoint FindClosestNeighbour(const TArray<FIntPoint>& Neighbours, const FIntPoint& Destination) const;

	// Connections
	void ConnectWithNextStage(int StageIndex);
	void CreateRoadFromTo(const FIntPoint& From, const FIntPoint& To);

protected:

	// Map settings
	UPROPERTY(VisibleAnywhere)
	TArray<UMapStageData*> MapStages;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMapNodeData> RoadNodeData;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMapNodeData> ForestNodeData;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMapNodeData> InteractableForestData;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMapNodeData> InteractableGraveyardData;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfStagesToGenerate = 5;
	UPROPERTY(EditDefaultsOnly)
	FVector MapStartLocation = {50000, 0, 0};
	UPROPERTY(EditDefaultsOnly)
	FIntPoint StageSize = {20, 10};
	UPROPERTY(EditDefaultsOnly)
	FIntPoint NodesInStageRange = {2, 5};
	UPROPERTY(EditDefaultsOnly)
	int POILocalYMargin = 3;
	UPROPERTY(EditDefaultsOnly)
	int POILocalXMargin = 1;

	UPROPERTY(EditDefaultsOnly)
	FVector2D NodeOffset = FVector2D(300, 250);

	// Runtime data
	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, AMapNode*> SpawnedNodes;

	// Player
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerMapPawn> PlayerMapPawnClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<APlayerMapPawn> PlayerMapPawn;

	// Debug
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDebugShowAllNodes = false;
};
