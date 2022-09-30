// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SmartPostProcessVolume.h"
#include "World/WorldLoaderSubsystem.h"

void ASmartPostProcessVolume::BeginPlay()
{
	if (bIsBoardVolume)
	{
		bUnbound = 0;
		SetActorLocation(BoardVolumeLocation);
		SetActorScale3D(BoardVolumeScale);
	}
	else
	{
		UWorldLoaderSubsystem* WorldLoader = GetGameInstance()->GetSubsystem<UWorldLoaderSubsystem>();
		if (WorldLoader)
		{
			WorldLoader->RegisterMapPostProcess(this);
		}
	}
}
