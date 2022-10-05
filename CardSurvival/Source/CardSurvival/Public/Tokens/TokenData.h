// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/StatisticID.h"
#include "TokenData.generated.h"

class UPrimaryDataAsset;

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Instant, Durable
};

USTRUCT(BlueprintType)
struct CARDSURVIVAL_API FTokenEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EStatisticID StatisticID;
	UPROPERTY(EditDefaultsOnly)
	int32 Impact;
};

UCLASS()
class CARDSURVIVAL_API UTokenData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	EStatusType GetStatusType() const { return Type; };
	UFUNCTION(BlueprintCallable)
	FText GetName() const { return Name; }
	UFUNCTION(BlueprintCallable)
	FText GetDescription() const { return Description; }
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintPure)
	const TArray<FTokenEffect>& GetEffects() const { return Effects; };

protected:
	UPROPERTY(EditDefaultsOnly)
	EStatusType Type;
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly)
	FText Description;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTokenEffect> Effects;
};
