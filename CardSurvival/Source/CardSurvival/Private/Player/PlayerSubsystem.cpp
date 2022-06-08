// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerSubsystem.h"
#include "Player/PlayerPawn.h"
#include "Utils/FollowComponent.h"

#include "Kismet/GameplayStatics.h"


TObjectPtr<APlayerPawn> UPlayerSubsystem::GetPlayerPawn() const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerPawn* Player = Cast<APlayerPawn>(PlayerController->GetPawn());

	return Player;
}

TObjectPtr<ACursor> UPlayerSubsystem::GetPlayerCursor3D() const
{
	return GetPlayerCursor3D(GetPlayerPawn());
}

TObjectPtr<ACursor> UPlayerSubsystem::GetPlayerCursor3D(const TObjectPtr<APlayerPawn> PlayerPawn) const
{
	return PlayerPawn->GetCursor3D();
}

const FHitResult& UPlayerSubsystem::GetHitResultUnderCursor() const
{
	APlayerPawn* Player = GetPlayerPawn();
	const FHitResult& HitResult = Player->GetHitResult();

	return HitResult;
}
