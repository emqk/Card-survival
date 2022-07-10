// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMapPawn.h"
#include "Utils/FollowComponent.h"
#include "Player/PlayerSubsystem.h"
#include "WorldMap/MapManager.h"
#include "Camera/CameraComponent.h" 

APlayerMapPawn::APlayerMapPawn()
{
	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}


void APlayerMapPawn::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->SetMapPlayer(this);
}

void APlayerMapPawn::MoveToWorldIndex(const FIntPoint& NewLocation)
{
	WorldLocationIndex = NewLocation;

	AMapManager* MapManager = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetMapManager();
	FVector NewLocation3D = MapManager->GetWorldLocationFromIndex(NewLocation) + WalkOffset;
	FollowComponent->SetFollow(nullptr, NewLocation3D, GetActorRotation());
}

void APlayerMapPawn::MoveToWorldIndex_Instant(const FIntPoint& NewLocation)
{
	WorldLocationIndex = NewLocation;

	AMapManager* MapManager = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetMapManager();
	FVector NewLocation3D = MapManager->GetWorldLocationFromIndex(NewLocation) + WalkOffset;
	SetActorLocation(NewLocation3D);
}
