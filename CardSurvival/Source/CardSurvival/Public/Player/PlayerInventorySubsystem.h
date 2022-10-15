// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Utils/StatisticID.h"
#include "Tokens/TokenData.h"
#include "PlayerInventorySubsystem.generated.h"

class UStatistic;

UCLASS()
class CARDSURVIVAL_API UPlayerInventorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	UStatistic* GetStatisticByID(EStatisticID ID) const;

	UFUNCTION(BlueprintPure)
	UStatistic* GetGold() const { return Gold; };
	UFUNCTION(BlueprintPure)
	UStatistic* GetHealth() const { return Health; };
	UFUNCTION(BlueprintPure)
	UStatistic* GetEnergy() const { return Energy; };
	UFUNCTION(BlueprintPure)
	UStatistic* GetSanity() const { return Sanity; };

	UFUNCTION(BlueprintCallable)
	void ApplyEffects(const TArray<FTokenEffect>& Effects, int32 Amount);
	UFUNCTION(BlueprintCallable)
	void ApplyEffect(const FTokenEffect& Effect, int32 Amount);

protected:
	UPROPERTY()
	TObjectPtr<UStatistic> Gold;
	UPROPERTY()
	TObjectPtr<UStatistic> Health;
	UPROPERTY()
	TObjectPtr<UStatistic> Energy;
	UPROPERTY()
	TObjectPtr<UStatistic> Sanity;
};
