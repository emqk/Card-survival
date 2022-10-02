// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardUseBase.generated.h"

class UCardData;

UCLASS(Blueprintable, EditInlineNew)
class CARDSURVIVAL_API UCardUseBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Use(ACardBase* From, ACardBase* To);

	bool IsCardAccepted(UCardData* CardData);

protected:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UCardData>> AcceptedCards;
};
