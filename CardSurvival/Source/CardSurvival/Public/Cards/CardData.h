// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tokens/TokenDataInstance.h"
#include "CardData.generated.h"

class UPrimaryDataAsset;

UENUM(BlueprintType)
enum class ECardCategory : uint8
{
	Equippable, Consumable, Usable, Interactable
};

UENUM(BlueprintType)
enum class ECardRarity : uint8
{
	Common, Rare, Epic, Legendary
};

UCLASS()
class CARDSURVIVAL_API UCardData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FText GetName() const { return Name; }
	UFUNCTION(BlueprintCallable)
	int32 GetStrength() const { return Strength; }
	UFUNCTION(BlueprintCallable)
	ECardCategory GetCategory() const { return Category; }
	UFUNCTION(BlueprintCallable)
	ECardRarity GetRarity() const { return Rarity; }
	UFUNCTION(BlueprintCallable)
	UParallaxData* GetParalaxData() const { return ParallaxData; }
	UFUNCTION(BlueprintCallable)
	const TArray<FTokenDataInstance>& GetStatuses() const { return Statuses; };

protected:
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly)
	int32 Strength;
	UPROPERTY(EditDefaultsOnly)
	ECardCategory Category;
	UPROPERTY(EditDefaultsOnly)
	ECardRarity Rarity;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParallaxData> ParallaxData;
	UPROPERTY(EditDefaultsOnly)
	TArray<FTokenDataInstance> Statuses;
};
