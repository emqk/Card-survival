// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayZone.generated.h"

class ACard;

UCLASS()
class CARDSURVIVAL_API APlayZone : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayZone();

	bool AddCard(ACard* CardToAdd);
	bool RemoveCard(ACard* CardToRemove);

protected:
	FVector GetCardLocationAtIndex(int Index);
	void RefreshCardsLocation();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	float Spacing = 400;

	UPROPERTY(VisibleAnywhere)
	TArray<ACard*> Cards;
};
