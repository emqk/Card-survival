// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerSubsystem.generated.h"

class APlayerPawn;
class UFollowComponent;
class ACursor;
class ATokenRow;

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
	TObjectPtr<APlayerPawn> GetPlayerPawn() const;
	TObjectPtr<ACursor> GetPlayerCursor3D() const;
	TObjectPtr<ACursor> GetPlayerCursor3D(const TObjectPtr<APlayerPawn> PlayerPawn) const;
	bool IsPlayerInteracting() const;
	const FHitResult& GetHitResultUnderCursor() const;

	// Tokens
	ATokenRow* GetTokenRow() const { return TokenRow; };

protected:
	UPROPERTY()
	TObjectPtr<ATokenRow> TokenRow = nullptr;
};
