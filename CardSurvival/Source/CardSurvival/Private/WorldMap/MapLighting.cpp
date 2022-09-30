// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapLighting.h"
#include "World/WorldLoaderSubsystem.h"
#include "Components/DirectionalLightComponent.h"

AMapLighting::AMapLighting()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	DirectionalLightComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLight"));
	DirectionalLightComponent->SetupAttachment(RootComponent);
}

void AMapLighting::Activate()
{
	DirectionalLightComponent->SetVisibility(true);
}

void AMapLighting::Deactivate()
{
	DirectionalLightComponent->SetVisibility(false);
}

void AMapLighting::BeginPlay()
{
	Super::BeginPlay();	

	UWorldLoaderSubsystem* WorldLoader = GetGameInstance()->GetSubsystem<UWorldLoaderSubsystem>();
	if (WorldLoader)
	{
		WorldLoader->RegisterMapLighting(this);
	}
}
