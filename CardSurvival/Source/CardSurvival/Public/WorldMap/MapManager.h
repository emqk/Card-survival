// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapManager.generated.h"

class AMapNode;

USTRUCT(BlueprintType)
struct FMapLevelData
{
	GENERATED_BODY();

public:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AMapNode>> Nodes;
};


UCLASS()
class CARDSURVIVAL_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:

	AMapManager();

	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintInitialize();


	UFUNCTION(BlueprintCallable)
	void CreateNewLevel();
	UFUNCTION(BlueprintCallable)
	AMapNode* SpawnNode(const FVector& Location);

	UFUNCTION(BlueprintCallable)
	void ConnectNodesInLevel(int32 LevelIndex);


protected:
	FVector FindLevelLocationByIndex(int32 LevelIndex);

protected:

	UPROPERTY(VisibleAnywhere)
	TArray<FMapLevelData> Levels;

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
