// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EventData.generated.h"

class UEventAction;

USTRUCT(BlueprintType)
struct FEventActionInitData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Chance;
};


USTRUCT(BlueprintType)
struct FEventActionData 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UEventAction> Actions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 99))
	FIntPoint ChanceRange = FIntPoint(1, 99);
};


UCLASS()
class CARDSURVIVAL_API UEventData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (MultiLine = "true"))
	FText Header;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> BackgroundTexture;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FEventActionData> ActionDatas;
};
