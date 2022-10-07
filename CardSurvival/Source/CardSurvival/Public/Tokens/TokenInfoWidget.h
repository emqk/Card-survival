// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TokenInfoWidget.generated.h"

/**
 * 
 */
UCLASS(meta = (DisableNativeTick))
class CARDSURVIVAL_API UTokenInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Refresh(UTokenData* TokenData, int32 Amount);
};
