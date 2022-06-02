// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapNodeConnection.h"
#include "Components/SplineComponent.h"

AMapNodeConnection::AMapNodeConnection()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(SceneComponent);
}