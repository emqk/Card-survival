// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMapPawn.h"
#include "Player/PlayerInventorySubsystem.h"
#include "Utils/FollowComponent.h"
#include "Utils/Statistic.h"
#include "Player/PlayerSubsystem.h"
#include "WorldMap/MapManager.h"
#include "WorldMap/WorldMapStatsWidget.h"
#include "Camera/CameraComponent.h" 
#include "Blueprint/UserWidget.h"

APlayerMapPawn::APlayerMapPawn()
{
	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}


void APlayerMapPawn::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->SetMapPlayer(this);

	WorldMapStatsWidgetInstance = CreateWidget<UWorldMapStatsWidget>(GetWorld(), WorldMapStatsWidgetClass);
	SetStatsActive(true);
}

void APlayerMapPawn::MoveToWorldIndex(const FIntPoint& NewLocation)
{
	WorldLocationIndex = NewLocation;

	AMapManager* MapManager = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetMapManager();
	FVector NewLocation3D = MapManager->GetWorldLocationFromIndex(NewLocation) + WalkOffset;
	FollowComponent->SetFollow(nullptr, NewLocation3D, GetActorRotation());

	SpawnNodesInView();
}

void APlayerMapPawn::MoveToWorldIndex_Instant(const FIntPoint& NewLocation)
{
	WorldLocationIndex = NewLocation;

	AMapManager* MapManager = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetMapManager();
	FVector NewLocation3D = MapManager->GetWorldLocationFromIndex(NewLocation) + WalkOffset;
	SetActorLocation(NewLocation3D);

	SpawnNodesInView();
}

void APlayerMapPawn::SetStatsActive(bool bActive)
{
	if (!WorldMapStatsWidgetInstance)
	{
		return;
	}

	if (bActive)
	{
		WorldMapStatsWidgetInstance->AddToViewport();	
		RefreshStats();
	}
	else
	{
		WorldMapStatsWidgetInstance->RemoveFromViewport();
	}
}

void APlayerMapPawn::Step()
{
	UPlayerInventorySubsystem* PlayerInventory = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();

	UStatistic* Energy = PlayerInventory->GetEnergy();
	int32 EnergyCost = GetEnergyDecreaseAfterStep();

	if (Energy->GetAmount() <= 0)
	{
		PlayerInventory->GetHealth()->ChangeByAmount(EnergyCost);
	}

	Energy->ChangeByAmount(EnergyCost);

	RefreshStats();
}

void APlayerMapPawn::SpawnNodesInView()
{
	AMapManager* MapManager = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetMapManager();
	MapManager->SpawnNodesInView(WorldLocationIndex, ViewDistance);
}
