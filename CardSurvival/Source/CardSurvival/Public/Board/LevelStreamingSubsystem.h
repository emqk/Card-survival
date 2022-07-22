// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelStreamingSubsystem.generated.h"

class ULevelStreamingDynamic;

UCLASS(BlueprintType)
class CARDSURVIVAL_API ULevelStreamingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void LoadLevelInstance(TSoftObjectPtr<UWorld> LevelInstanceToLoad, const FVector& Offset);
	void UnloadCurrentLevelInstance();

protected:
	UPROPERTY()
	ULevelStreamingDynamic* CurrentLevel = nullptr;
};
