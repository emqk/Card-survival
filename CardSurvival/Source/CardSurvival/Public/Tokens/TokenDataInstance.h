// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TokenDataInstance.generated.h"

class UTokenData;

/**
 * 
 */
USTRUCT(BlueprintType)
struct CARDSURVIVAL_API FTokenDataInstance
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTokenData> TokenData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount = 0;
};
