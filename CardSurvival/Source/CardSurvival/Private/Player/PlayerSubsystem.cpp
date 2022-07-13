// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerSubsystem.h"
#include "Player/PlayerBoardPawn.h"
#include "Player/OwnPlayerController.h"
#include "Utils/FollowComponent.h"
#include "Tokens/TokenRow.h"
#include "WorldMap/MapManager.h"

#include "Kismet/GameplayStatics.h"


TObjectPtr<AOwnPlayerController> UPlayerSubsystem::GetPlayerController() const
{
	AOwnPlayerController* PlayerController = Cast<AOwnPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	return PlayerController;
}

TObjectPtr<ACursor> UPlayerSubsystem::GetPlayerCursor3D() const
{
	AOwnPlayerController* PlayerController = GetPlayerController();
	if (!PlayerController)
	{
		return nullptr;
	}

	return PlayerController->GetCursor3D();
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
