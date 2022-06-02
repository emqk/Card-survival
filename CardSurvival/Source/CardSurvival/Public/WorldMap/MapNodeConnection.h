// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNodeConnection.generated.h"

class USplineComponent;

UCLASS()
class CARDSURVIVAL_API AMapNodeConnection : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapNodeConnection();


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> SplineComponent;
};
