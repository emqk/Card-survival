// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Cards/CardData.h"
#include "LevelInstance/LevelInstanceActor.h"
#include "EnvironmentData.generated.h"

/**
 * 
 */
UCLASS()
class CARDSURVIVAL_API UEnvironmentData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	const TSoftObjectPtr<UWorld>& GetLevelInstance() const { return LevelInstance; };

	UFUNCTION(BlueprintPure)
	const TArray<FCardSpawnData>& GetCardSpawnData() const { return CardSpawnData; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> LevelInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCardSpawnData> CardSpawnData;
};
