// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventAction.generated.h"

UCLASS(Blueprintable)
class CARDSURVIVAL_API UEventAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Perform();

	UFUNCTION(BlueprintPure)
	AEventsManager* GetEventsManager() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayText;
};
 