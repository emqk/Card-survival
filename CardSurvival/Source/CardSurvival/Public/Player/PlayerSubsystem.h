// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerSubsystem.generated.h"

class APlayerBoardPawn;
class UPlayZoneComponent;
class UInteractionComponent;
class APlayerMapPawn;
class AOwnPlayerController;
class UFollowComponent;
class ACursor;
class ATokenRow;
class AMapManager;
class AEventsManager;
class ACardManager;
class ABoard;

/**
 * Player utils
 */
UCLASS()
class CARDSURVIVAL_API UPlayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// Player
	void SetBoardPlayer(APlayerBoardPawn* PlayerPawn) { BoardPlayer = PlayerPawn; };
	void SetMapPlayer(APlayerMapPawn* PlayerPawn) { MapPlayer = PlayerPawn; };

	UFUNCTION(BlueprintPure)
	APlayerBoardPawn* GetPlayerBoardPawn() const { return BoardPlayer; };
	UFUNCTION(BlueprintPure)
	APlayerMapPawn* GetPlayerMapPawn() const { return MapPlayer; };
	
	TObjectPtr<AOwnPlayerController> GetPlayerController() const;

	TObjectPtr<ACursor> GetPlayerCursor3D() const;
	bool IsPlayerInteracting() const;
	UInteractionComponent* GetInteractionComponentBoard() const;
	const FHitResult& GetHitResultUnderCursor() const;

	// Tokens
	void SetTokenRow(ATokenRow* NewTokenRow) { TokenRow = NewTokenRow; };
	ATokenRow* GetTokenRow() const { return TokenRow; };
	void SetMapManager(AMapManager* NewMapManager) { MapManager = NewMapManager; };
	AMapManager* GetMapManager() const { return MapManager; };

	// Events
	void SetEventsManager(AEventsManager* NewEventsManager) { EventsManager = NewEventsManager; };
	UFUNCTION(BlueprintPure)
	AEventsManager* GetEventsManager() const { return EventsManager; };

	// Cards
	void SetCardManager(ACardManager* NewCardManager) { CardManager = NewCardManager; };
	UFUNCTION(BlueprintPure)
	ACardManager* GetCardManager();

	// Board
	void SetBoard(ABoard* NewBoard) { Board = NewBoard; };
	UFUNCTION(BlueprintPure)
	ABoard* GetBoard();
	UPlayZoneComponent* GetPlayZoneFromLocation(const FVector2D& Location2D) const;

protected:
	UPROPERTY()
	TObjectPtr<ATokenRow> TokenRow = nullptr;
	UPROPERTY()
	TObjectPtr<AMapManager> MapManager = nullptr;
	UPROPERTY()
	TObjectPtr<AEventsManager> EventsManager = nullptr;
	UPROPERTY()
	TObjectPtr<ACardManager> CardManager = nullptr;
	UPROPERTY()
	TObjectPtr<ABoard> Board = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerBoardPawn> BoardPlayer = nullptr;
	UPROPERTY()
	TObjectPtr<APlayerMapPawn> MapPlayer = nullptr;
};
