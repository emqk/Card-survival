// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayZoneComponent.generated.h"

class ACard;

UCLASS()
class CARDSURVIVAL_API UPlayZoneComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:	
	UPlayZoneComponent();

	bool AddCard(TObjectPtr<ACard> CardToAdd);
	bool RemoveCard(TObjectPtr<ACard> CardToRemove);

protected:
	FVector GetCardLocationAtIndex(int Index);
	void RefreshCardsLocation();

protected:
	UPROPERTY(EditAnywhere)
	int NumberOfRows = 1;

	UPROPERTY(EditDefaultsOnly)
	float SpacingX = 600;
	UPROPERTY(EditDefaultsOnly)
	float SpacingY = 400;
	UPROPERTY(EditDefaultsOnly)
	float OffsetZ = 0;

	UPROPERTY(EditDefaultsOnly)
	float DefaultOffsetY = 0;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<ACard>> Cards;
};