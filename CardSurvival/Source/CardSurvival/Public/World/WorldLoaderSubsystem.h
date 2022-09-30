// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WorldLoaderSubsystem.generated.h"

class AMapLighting;
class ASmartPostProcessVolume;
class UEnvironmentData;

UCLASS()
class CARDSURVIVAL_API UWorldLoaderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	void OpenNewEnvironment(UEnvironmentData* EnvironmentData);
	void OpenMap();

	void RegisterMapLighting(AMapLighting* NewMapLighting) { MapLighting = NewMapLighting; };
	AMapLighting* GetMapLighting() { return MapLighting; };
	
	void RegisterMapPostProcess(ASmartPostProcessVolume* NewMapPostProcess) { MapPostProcess = NewMapPostProcess; };
	ASmartPostProcessVolume* GetMapPostProcess() { return MapPostProcess; };

protected:
	UPROPERTY()
	TObjectPtr<AMapLighting> MapLighting;
	UPROPERTY()
	TObjectPtr<ASmartPostProcessVolume> MapPostProcess;
};
