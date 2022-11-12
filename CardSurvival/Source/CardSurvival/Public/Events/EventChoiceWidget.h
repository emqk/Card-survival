// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventChoiceWidget.generated.h"

class UEventAction;

UCLASS()
class CARDSURVIVAL_API UEventChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetActionClass(UEventAction* NewAction) { Action = NewAction; };

	UFUNCTION(BlueprintCallable)
	int GetChance() const { return Chance; };
	UFUNCTION(BlueprintCallable)
	void SetChance(int NewChance) { Chance = NewChance; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UEventAction> Action;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Chance;
};
