// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/StatisticID.h"
#include "TokenData.generated.h"

class UPrimaryDataAsset;

/**
 * 
 */
UCLASS()
class CARDSURVIVAL_API UTokenData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FText GetName() const { return Name; }
	UFUNCTION(BlueprintCallable)
	FText GetDescription() const { return Description; }
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetMesh() const { return Mesh; }


	UFUNCTION(BlueprintCallable, Category = "Effect")
	EStatisticID GetStatisticID() const { return StatisticID; };
	UFUNCTION(BlueprintCallable, Category = "Effect")
	int32 GetImpact() const { return Impact; };

protected:
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly)
	FText Description;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Effect")
	EStatisticID StatisticID;
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	int32 Impact;
};
