// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapManager.generated.h"

class AMapNode;

UCLASS()
class CARDSURVIVAL_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:

	AMapManager();

	UFUNCTION(BlueprintCallable)
	AMapNode* SpawnNode(const FVector& Location);

protected:
	FVector FindLevelLocationByIndex(int32 LevelIndex);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> MapNodeClass;
	UPROPERTY(EditDefaultsOnly)
	FVector MapLevelStartLocation = {10000, 0, 0};
	UPROPERTY(EditDefaultsOnly)
	FVector2D LevelSize = {2000, 1000};
	UPROPERTY(EditDefaultsOnly)
	float NodeSize = 100;
	UPROPERTY(EditDefaultsOnly)
	FIntPoint NodesInLevelRange = {2, 5};
};
