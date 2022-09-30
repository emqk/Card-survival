// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "SmartPostProcessVolume.generated.h"

UCLASS()
class CARDSURVIVAL_API ASmartPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	bool bIsBoardVolume = false;

private:
	FVector BoardVolumeLocation = FVector(0, 0, 0);
	FVector BoardVolumeScale = FVector(100, 100, 200);
};
