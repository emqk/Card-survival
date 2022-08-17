// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/CardData.h"
#include "Engine/DataAsset.h"
#include "CardSettings.generated.h"

UCLASS()
class CARDSURVIVAL_API UCardSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FLinearColor GetRarityColor(ECardRarity Rarity) const{ return RarityColors[Rarity]; }
	FLinearColor GetCategoryColor(ECardCategory Category) const{ return CategoryColors[Category]; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECardRarity, FLinearColor> RarityColors;
	UPROPERTY(EditDefaultsOnly)
	TMap<ECardCategory, FLinearColor> CategoryColors;
};