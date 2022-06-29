// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TokenAmountWidget.generated.h"

/**
 * 
 */
UCLASS(meta = (DisableNativeTick))
class CARDSURVIVAL_API UTokenAmountWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Refresh(int32 Amount);
};
