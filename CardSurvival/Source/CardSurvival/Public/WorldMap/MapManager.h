// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldMap/MapStageData.h"
#include "MapManager.generated.h"

class AMapNode;

UCLASS()
class CARDSURVIVAL_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:

	AMapManager();

	UFUNCTION(BlueprintCallable)
	void GenerateNextStage();
	UFUNCTION(BlueprintCallable)
	void SpawnNodes();

protected:
	AMapNode* SpawnNode(const FVector& Location, const TSubclassOf<AMapNode>& ClassToSpawn);
	FVector FindStageLocationByIndex(int32 StageIndex);
	FIntPoint GetGlobalMapStageOffset(const FMapStageData& MapStage) const;
	FIntPoint GetGlobalXY(const FMapStageData& MapStage, int LocalX, int LocalY) const;
	bool SetGlobalXY(int GlobalX, int GlobalY, int Value);


protected:

	UPROPERTY(VisibleAnywhere)
	TArray<FMapStageData> MapStages;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> RoadNodeClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> EnviroNodeClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> InteractableForestClass;

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
};
