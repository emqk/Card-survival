// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/CardUseBase.h"
#include "CardData.h"
#include "CardUseSpawnItems.generated.h"

UCLASS()
class CARDSURVIVAL_API UCardUseSpawnItems : public UCardUseBase
{
	GENERATED_BODY()
	
public:
	void Use_Implementation(ACardBase* From, ACardBase* To) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FCardSpawnData> CardsToSpawn;
};
