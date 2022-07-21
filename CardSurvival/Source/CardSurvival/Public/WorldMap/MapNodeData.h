// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNodeData.generated.h"

class UPrimaryDataAsset;
class AMapNode;

UCLASS(BlueprintType)
class CARDSURVIVAL_API UMapNodeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	TSubclassOf<AMapNode> GetNodeClass() const { return NodeClass; };
	TSoftObjectPtr<UWorld> GetLevelInstance() const { return LevelInstance; };
	bool GetIsWalkable() const { return bIsWalkable; };

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> NodeClass;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> LevelInstance;
	UPROPERTY(EditDefaultsOnly)
	bool bIsWalkable = false;
};
