// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerSubsystem.h"
#include "Player/PlayerBoardPawn.h"
#include "Utils/FollowComponent.h"
#include "Tokens/TokenRow.h"
#include "WorldMap/MapManager.h"

#include "Kismet/GameplayStatics.h"



void UPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TokenRow = Cast<ATokenRow>(UGameplayStatics::GetActorOfClass(GetWorld(), ATokenRow::StaticClass()));
	MapManager = Cast<AMapManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMapManager::StaticClass()));
}

TObjectPtr<ACursor> UPlayerSubsystem::GetPlayerCursor3D() const
{
	return GetPlayerCursor3D(GetPlayerBoardPawn());
}

TObjectPtr<ACursor> UPlayerSubsystem::GetPlayerCursor3D(const TObjectPtr<APlayerBoardPawn> PlayerPawn) const
{
	return PlayerPawn->GetCursor3D();
}

bool UPlayerSubsystem::IsPlayerInteracting() const
{
	APlayerPawn* Player = GetPlayerBoardPawn();
	return Player->IsInteracting();
}

const FHitResult& UPlayerSubsystem::GetHitResultUnderCursor() const
{
	APlayerPawn* Player = GetPlayerBoardPawn();
	const FHitResult& HitResult = Player->GetHitResult();

	return HitResult;
}
