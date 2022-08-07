// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventGambleWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDSURVIVAL_API UEventGambleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Start();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void End();

protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsGambling = false;
};
