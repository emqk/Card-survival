// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardInfoWidget.generated.h"

/**
 * 
 */
UCLASS(meta = (DisableNativeTick))
class CARDSURVIVAL_API UCardInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Refresh(UCardData* CardData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSelected();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnselected();
};
