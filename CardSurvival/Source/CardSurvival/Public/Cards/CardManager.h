// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardManager.generated.h"

class UCardSettings;

UCLASS()
class CARDSURVIVAL_API ACardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardManager();

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	UCardSettings* GetCardsSettings() const { return CardSettings; };

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCardSettings> CardSettings;
};
