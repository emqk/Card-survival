// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerPawn.h"
#include "PlayerBoardPawn.generated.h"

/**
 * 
 */
UCLASS()
class CARDSURVIVAL_API APlayerBoardPawn : public APlayerPawn
{
	GENERATED_BODY()
	
public:
	APlayerBoardPawn();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCardInfoActive(UCardData* CardData, bool bActive);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetBlackScreenActive(bool bActive);
};
