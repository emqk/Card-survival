// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Statistic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChange, UStatistic*, ModifiedStatistic);


UCLASS(BlueprintType, EditInlineNew)
class UStatistic : public UObject
{
    GENERATED_BODY()
public:
    UStatistic();
    ~UStatistic();

    UFUNCTION(BlueprintCallable)
    void ChangeByAmount(int _Amount);
    UFUNCTION(BlueprintCallable)
    void SetAmount(int _Amount);
	UFUNCTION(BlueprintCallable)
	void SetToMin();
	UFUNCTION(BlueprintCallable)
    void SetToMax();
	UFUNCTION(BlueprintCallable)
	void SetMaxAmount(int NewMaxAmount);

    UFUNCTION(BlueprintCallable)
    float GetAmountNormalized() const;
    UFUNCTION(BlueprintCallable)
    int GetAmount() const;

    // Is the amount after subtraction >= 0 ?
    UFUNCTION(BlueprintPure)
    bool CanSubtract(int ToSubtract) const;
    UFUNCTION(BlueprintPure)
    bool IsMax();

public:
	UPROPERTY(BlueprintAssignable)
	FAttributeChange OnAttributeChange;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int MaxAmount = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MinAmount = 0;
    UPROPERTY(VisibleAnywhere)
    int Amount = 0;
};