// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerSubsystem.h"
#include "Player/PlayerBoardPawn.h"
#include "Player/OwnPlayerController.h"
#include "Utils/FollowComponent.h"
#include "Tokens/TokenRow.h"
#include "WorldMap/MapManager.h"
#include "Cards/CardManager.h"
#include "Board/Board.h"

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

ACardManager* UPlayerSubsystem::GetCardManager()
{
	if (CardManager)
	{
		return CardManager;
	}
	
	ACardManager* NewCardManager = Cast<ACardManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACardManager::StaticClass()));
	SetCardManager(NewCardManager);

	return CardManager;
}

ABoard* UPlayerSubsystem::GetBoard()
{
	if (Board)
	{
		return Board;
	}

	ABoard* NewBoard = Cast<ABoard>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoard::StaticClass()));
	SetBoard(NewBoard);

	return Board;
}

UPlayZoneComponent* UPlayerSubsystem::GetPlayZoneFromLocation(const FVector2D& Location2D) const
{
	if (Board)
	{
		return Board->GetPlayZoneFromLocation(Location2D);
	}

	return nullptr;
}
