// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerInventorySubsystem.h"
#include "Utils/Statistic.h"
#include "Tokens/TokenData.h"

void UPlayerInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Create statistics
	Gold = NewObject<UStatistic>();
	Health = NewObject<UStatistic>();
	Energy = NewObject<UStatistic>();
	Sanity = NewObject<UStatistic>();

	// Set initial values
	Gold->SetMaxAmount(TNumericLimits<int32>::Max());
	Gold->SetAmount(123);
	Health->SetToMax();
	Energy->SetToMax();
	Sanity->SetToMax();
}

UStatistic* UPlayerInventorySubsystem::GetStatisticByID(EStatisticID ID) const
{
	switch (ID)
	{
		case EStatisticID::Gold: return Gold;
		case EStatisticID::Health: return Health;
		case EStatisticID::Energy: return Energy;
		case EStatisticID::Sanity: return Sanity;
	}

	return nullptr;
}

void UPlayerInventorySubsystem::ApplyEffects(const TArray<FTokenEffect>& Effects, int32 Amount)
{
	for (const FTokenEffect& Effect : Effects)
	{
		ApplyEffect(Effect, Amount);
	}
}

void UPlayerInventorySubsystem::ApplyEffect(const FTokenEffect& Effect, int32 Amount)
{
	UStatistic* Stat = GetStatisticByID(Effect.StatisticID);
	if (Stat)
	{
		int32 TokenCount = Amount;
		Stat->ChangeByAmount(Effect.Impact * TokenCount);
	}
}
