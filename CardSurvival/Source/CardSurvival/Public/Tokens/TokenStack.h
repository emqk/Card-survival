// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TokenStack.generated.h"

class AToken;
class UTokenData;

UCLASS()
class CARDSURVIVAL_API UTokenStack : public UObject
{
	GENERATED_BODY()

public:
	bool IsTokenOnTop(AToken* Token);

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTokenData> Data;

	UPROPERTY(VisibleAnywhere)
	TArray<AToken*> Tokens;

};
