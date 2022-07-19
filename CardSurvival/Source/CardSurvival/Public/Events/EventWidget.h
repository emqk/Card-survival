// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventWidget.generated.h"

class UEventData;

UCLASS()
class CARDSURVIVAL_API UEventWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowEvents(UEventData* EventData);
};