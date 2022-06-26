// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParallaxData.generated.h"

class UPrimaryDataAsset;

/**
 * 
 */
UCLASS()
class CARDSURVIVAL_API UParallaxData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UTexture* GetBaseTexture() const { return BaseTexture; }
	UFUNCTION(BlueprintCallable)
	UTexture* GetDepthTexture() const { return DepthTexture; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture> BaseTexture;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture> DepthTexture;
};
