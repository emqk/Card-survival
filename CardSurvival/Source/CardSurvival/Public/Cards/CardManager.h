// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardManager.generated.h"

class UCardSettings;
class ACard;
class ACardDummy;

UENUM(BlueprintType)
enum class EBoardRow : uint8
{
	EQ,
	PlayerInventory,
	Location
};

UCLASS()
class CARDSURVIVAL_API ACardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardManager();

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	UCardSettings* GetCardsSettings() const { return CardSettings; };

	UFUNCTION(BlueprintCallable)
	bool SpawnCardInRow(EBoardRow BoardRow, UCardData* CardData);
	UFUNCTION(BlueprintCallable)
	void DestroyAllCardsInRow(EBoardRow BoardRow);

	UFUNCTION(BlueprintCallable)
	ACardDummy* EnableCardDummy();
	UFUNCTION(BlueprintCallable)
	void DisableCardDummy();

	UFUNCTION(BlueprintCallable)
	UPlayZoneComponent* GetBoardRowFromEnum(EBoardRow BoardRow) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCardSettings> CardSettings;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACard> CardClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACardDummy> CardDummyClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACardDummy> CardDummyInstance;
};
