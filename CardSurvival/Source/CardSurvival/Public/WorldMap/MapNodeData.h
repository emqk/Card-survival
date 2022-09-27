// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Board/EnvironmentData.h"
#include "MapNodeData.generated.h"

class UPrimaryDataAsset;
class AMapNode;

UCLASS(BlueprintType)
class CARDSURVIVAL_API UMapNodeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	TSubclassOf<AMapNode> GetNodeClass() const { return NodeClass; };
	UEnvironmentData* GetEnvironmentData() const { return EnvironmentData; };
	int32 GetVisibility() const { return Visibility; };
	bool GetIsWalkable() const { return bIsWalkable; };

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> NodeClass;
	UPROPERTY(EditDefaultsOnly)
	UEnvironmentData* EnvironmentData;
	UPROPERTY(EditDefaultsOnly)
	int32 Visibility = 1;
	UPROPERTY(EditDefaultsOnly)
	bool bIsWalkable = false;
};
