// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
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
	TSoftObjectPtr<UWorld> GetLevelInstance() const { return LevelInstance; };
	UFUNCTION(BlueprintCallable)
	FVector GetOffset() const { return Offset; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> LevelInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector Offset;
};