// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Statistic.generated.h"


UCLASS(BlueprintType, EditInlineNew)
class UStatistic : public UObject
{
    GENERATED_BODY()
public:
    UStatistic();
    ~UStatistic();

    UFUNCTION(BlueprintCallable)
    void ChangeByAmount(const float& _Amount);
    UFUNCTION(BlueprintCallable)
    void SetAmount(const float& _Amount);
	UFUNCTION(BlueprintCallable)
	void SetToMin();

    UFUNCTION(BlueprintCallable)
    float GetAmountNormalized() const;
    UFUNCTION(BlueprintCallable)
    float GetAmount() const;

    // Is the amount after subtraction >= 0 ?
    UFUNCTION(BlueprintPure)
    bool CanSubtract(float ToSubtract) const;
    UFUNCTION(BlueprintPure)
    bool IsMax();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxAmount = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinAmount = 0.0f;
    UPROPERTY(VisibleAnywhere)
    float Amount = 0.0f;
};