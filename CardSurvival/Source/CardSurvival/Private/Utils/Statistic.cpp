// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Statistic.h"

UStatistic::UStatistic()
{
}

UStatistic::~UStatistic()
{
}

void UStatistic::ChangeByAmount(int _Amount)
{
	SetAmount(Amount + _Amount);
}

void UStatistic::SetAmount(int _Amount)
{
	Amount = FMath::Clamp(_Amount, MinAmount, MaxAmount);
	OnAttributeChange.Broadcast(this);
}

void UStatistic::SetToMin()
{
	Amount = MinAmount;
	OnAttributeChange.Broadcast(this);
}

void UStatistic::SetToMax()
{
	SetAmount(MaxAmount);
}

void UStatistic::SetMaxAmount(int NewMaxAmount)
{
	MaxAmount = NewMaxAmount;
}

float UStatistic::GetAmountNormalized() const
{
	return GetAmount() / (float)MaxAmount;
}

int UStatistic::GetAmount() const
{
	return Amount;
}

bool UStatistic::CanSubtract(int ToSubtract) const
{
	return (Amount - ToSubtract) >= 0;
}

bool UStatistic::IsMax()
{
	return Amount >= MaxAmount;
}
