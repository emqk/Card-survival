// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/LevelStreamingSubsystem.h"
#include "Engine/LevelStreamingDynamic.h"

void ULevelStreamingSubsystem::LoadLevelInstance(TSoftObjectPtr<UWorld> LevelInstanceToLoad, const FVector& Offset)
{
	if (CurrentLevel)
	{
		UnloadCurrentLevelInstance();
	}

	bool bOutSuccess;
	CurrentLevel = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GetWorld(), LevelInstanceToLoad, Offset, FRotator(), bOutSuccess);
}

void ULevelStreamingSubsystem::UnloadCurrentLevelInstance()
{
	if (CurrentLevel)
	{
		CurrentLevel->SetShouldBeLoaded(false);
		CurrentLevel = nullptr;
	}
}
