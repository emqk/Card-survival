// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapLighting.generated.h"

class UDirectionalLightComponent;

UCLASS()
class CARDSURVIVAL_API AMapLighting : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapLighting();

	void Activate();
	void Deactivate();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDirectionalLightComponent> DirectionalLightComponent;
};
