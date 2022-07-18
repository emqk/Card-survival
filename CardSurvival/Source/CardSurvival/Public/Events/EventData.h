// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EventData.generated.h"

class UEventAction;

UCLASS()
class CARDSURVIVAL_API UEventData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Header;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UEventAction>> Actions;
};
