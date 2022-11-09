// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/StatisticBoard.h"

AStatisticBoard::AStatisticBoard()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(SceneComponent);

	HealthBarComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthBar"));
	HealthBarComponent->SetupAttachment(BaseMeshComponent);
	EnergyBarComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnergyBar"));
	EnergyBarComponent->SetupAttachment(BaseMeshComponent);
}
