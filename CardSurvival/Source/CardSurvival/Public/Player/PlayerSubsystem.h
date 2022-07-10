// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerSubsystem.generated.h"

class APlayerPawn;
class APlayerMapPawn;
class UFollowComponent;
class ACursor;
class ATokenRow;
class AMapManager;

/**
 * Player utils
 */
UCLASS()
class CARDSURVIVAL_API UPlayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// Overrides
	void Initialize(FSubsystemCollectionBase& Collection) override;
	
	// Player
	void SetBoardPlayer(APlayerPawn* PlayerPawn) { BoardPlayer = PlayerPawn; };
	void SetMapPlayer(APlayerMapPawn* PlayerPawn) { MapPlayer = PlayerPawn; };

	TObjectPtr<APlayerPawn> GetPlayerBoardPawn() const { return BoardPlayer; };
	TObjectPtr<APlayerMapPawn> GetPlayerMapPawn() const { return MapPlayer; };

	TObjectPtr<ACursor> GetPlayerCursor3D() const;
	TObjectPtr<ACursor> GetPlayerCursor3D(const TObjectPtr<APlayerPawn> PlayerPawn) const;
	bool IsPlayerInteracting() const;
	const FHitResult& GetHitResultUnderCursor() const;

	// Tokens
	ATokenRow* GetTokenRow() const { return TokenRow; };
	AMapManager* GetMapManager() const { return MapManager; };

protected:
	UPROPERTY()
	TObjectPtr<ATokenRow> TokenRow = nullptr;
	UPROPERTY()
	TObjectPtr<AMapManager> MapManager = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerPawn> BoardPlayer = nullptr;
	UPROPERTY()
	TObjectPtr<APlayerMapPawn> MapPlayer = nullptr;
};
