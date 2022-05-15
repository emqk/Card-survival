// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Cursor.h"

ACursor::ACursor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);
}

