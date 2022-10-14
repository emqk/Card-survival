// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayZoneComponent.generated.h"

class ACardBase;
class ACard;
class ACardDummy;

UCLASS()
class CARDSURVIVAL_API UPlayZoneComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:	
	UPlayZoneComponent();

	bool AddCard(ACardBase* CardToAdd, int32 Index = INDEX_NONE);
	bool RemoveCard(ACardBase* CardToRemove);
	void MoveCardToIndex(ACardBase* CardToMove, int32 NewIndex);

	void DestroyCard(ACardBase* Card);
	void DestroyAllCards();

	int32 GetCardIndex(ACardBase* Card) const;
	int32 GetCardIndexFromLocation(const FVector& GlobalLocation);

	bool IsLocationInPlayZone(const FVector2D& Location2D);
	bool IsRowFull() const { return Cards.Num() >= MaxNumberOfCards; }

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

	UPROPERTY(EditDefaultsOnly)
	int32 MaxNumberOfCards = 6;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<ACardBase>> Cards;
};
