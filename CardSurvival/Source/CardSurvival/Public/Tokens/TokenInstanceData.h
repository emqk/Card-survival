// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TokenInstanceData.generated.h"

class AToken;
class UTokenData;

USTRUCT()
struct CARDSURVIVAL_API FTokenInstanceData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTokenData> Data;
	UPROPERTY(VisibleAnywhere)
	TArray<AToken*> Tokens;
};
