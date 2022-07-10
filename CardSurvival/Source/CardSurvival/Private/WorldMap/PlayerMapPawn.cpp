// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/PlayerMapPawn.h"
#include "Utils/FollowComponent.h"

APlayerMapPawn::APlayerMapPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}
