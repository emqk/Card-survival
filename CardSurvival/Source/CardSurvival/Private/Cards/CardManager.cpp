// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardManager.h"
#include "Player/PlayerSubsystem.h"

ACardManager::ACardManager()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
}

void ACardManager::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->SetCardManager(this);
}
