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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Display(UEventData* NewEventData);
	UFUNCTION(BlueprintCallable)
	void GoToFirstStage();
	UFUNCTION(BlueprintCallable)
	void NextStage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnNextStageOpen(int Stage);

	bool ShouldEnd() { return CurrentStage >= 2; };

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UEventData> EventData;

	// -1 = Not started. 0 = First stage
	UPROPERTY(BlueprintReadWrite)
	int CurrentStage = -1;
};
