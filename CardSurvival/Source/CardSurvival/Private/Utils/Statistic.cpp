// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Statistic.h"

UStatistic::UStatistic()
{
}

UStatistic::~UStatistic()
{
}

void UStatistic::ChangeByAmount(const float& _Amount)
{
	SetAmount(Amount + _Amount);
}

void UStatistic::SetAmount(const float& _Amount)
{
	Amount = FMath::Clamp(_Amount, MinAmount, MaxAmount);
}

void UStatistic::SetToMin()
{
	Amount = MinAmount;
}

float UStatistic::GetAmountNormalized() const
{
	return GetAmount() / MaxAmount;
}

float UStatistic::GetAmount() const
{
	return Amount;
}

bool UStatistic::CanSubtract(float ToSubtract) const
{
	return (Amount - ToSubtract) >= 0.0f;
}

bool UStatistic::IsMax()
{
	return Amount >= MaxAmount;
}
