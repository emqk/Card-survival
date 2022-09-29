// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SmartPostProcessVolume.h"

void ASmartPostProcessVolume::BeginPlay()
{
	if (bIsBoardVolume)
	{
		bUnbound = 0;
		SetActorLocation(BoardVolumeLocation);
		SetActorScale3D(BoardVolumeScale);
	}
}
