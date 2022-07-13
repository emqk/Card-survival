// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldMap/MapStageData.h"
#include "MapManager.generated.h"

class AMapNode;
class APlayerMapPawn;

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
	void SpawnNodes();

	FVector GetWorldLocationFromIndex(const FIntPoint& WorldIndex) const;
	FIntPoint ConvertWorldLocationToMapIndex(const FVector& WorldLocation) const;

	bool IsNodeWalkable(const FIntPoint& WorldIndex) const;

protected:
	AMapNode* SpawnNode(const FVector& Location, const TSubclassOf<AMapNode>& ClassToSpawn);
	FVector FindStageLocationByIndex(int32 StageIndex);
	FIntPoint GetGlobalMapStageOffset(const UMapStageData* MapStage) const;
	FIntPoint GetGlobalXY(const UMapStageData* MapStage, int LocalX, int LocalY) const;
	bool SetDataGlobalXY(int GlobalX, int GlobalY, int Value);
	int GetDataGlobalXY(int GlobalX, int GlobalY) const;

protected:

	// Map settings
	UPROPERTY(VisibleAnywhere)
	TArray<UMapStageData*> MapStages;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> RoadNodeClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> EnviroNodeClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> InteractableForestClass;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfStagesToGenerate = 5;
	UPROPERTY(EditDefaultsOnly)
	FVector MapStartLocation = {10000, 0, 0};
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


	// Player
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerMapPawn> PlayerMapPawnClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<APlayerMapPawn> PlayerMapPawn;
};
