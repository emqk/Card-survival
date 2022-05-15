// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerSubsystem.generated.h"

class APlayerPawn;
class UFollowComponent;
class ACursor;

/**
 * Player utils
 */
UCLASS()
class CARDSURVIVAL_API UPlayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	APlayerPawn* GetPlayerPawn() const;
	ACursor* GetPlayerCursor3D() const;
	ACursor* GetPlayerCursor3D(const APlayerPawn* PlayerPawn) const;
};
