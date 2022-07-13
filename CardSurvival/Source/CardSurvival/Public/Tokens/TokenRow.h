// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TokenRow.generated.h"

class AToken;
class UTokenStack;

UCLASS()
class CARDSURVIVAL_API ATokenRow : public AActor
{
	GENERATED_BODY()
	
public:	
	ATokenRow();
	
	// Overrides
	void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void AddTokens(UTokenData* Data, int32 Amount);
	UFUNCTION(BlueprintCallable)
	void AddToken(UTokenData* Data);
	UFUNCTION(BlueprintCallable)
	void RemoveToken(UTokenData* Data);

protected:
	void RefreshTokensLocation();

	int FindTokenIndexWithData(const UTokenData* Data) const;
	FVector FindLocationForToken(int RowIndex, int TokenHeight);
	float GetLocationXFromIndex(int Index) const;
	float GetLocationZFromAmount(int Amount) const;

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UTokenStack>> TokenStacks;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AToken> TokenClass;
	UPROPERTY(EditDefaultsOnly)
	float SpacingX = 150.0f;
	UPROPERTY(EditDefaultsOnly)
	float SpacingZ = 50.0f;
};
