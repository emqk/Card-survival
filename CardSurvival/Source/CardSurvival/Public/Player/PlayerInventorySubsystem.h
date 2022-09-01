// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerInventorySubsystem.generated.h"

class UStatistic;

UCLASS()
class CARDSURVIVAL_API UPlayerInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintPure)
	UStatistic* GetGold() const { return Gold; };
	UFUNCTION(BlueprintPure)
	UStatistic* GetHealth() const { return Health; };
	UFUNCTION(BlueprintPure)
	UStatistic* GetEnergy() const { return Energy; };
	UFUNCTION(BlueprintPure)
	UStatistic* GetSanity() const { return Sanity; };

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
