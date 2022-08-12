// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Events/EventData.h"
#include "GameFramework/Actor.h"
#include "EventsManager.generated.h"

class UEventWidget;

UCLASS()
class CARDSURVIVAL_API AEventsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEventsManager();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartEvent(UEventData* EventData);
	UFUNCTION(BlueprintCallable)
	void NextStage();
	UFUNCTION(BlueprintCallable)
	void EndEvent();

	UFUNCTION(BlueprintCallable)
	void SetEventActionInitData(const FEventActionInitData& NewEventActionInitData) { EventActionInitData = NewEventActionInitData; }
	UFUNCTION(BlueprintCallable)
	FEventActionInitData GetEventActionInitData() const { return EventActionInitData; };

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEventWidget> EventWidgetClass;
	UPROPERTY(VisibleAnywhere)
	UEventWidget* EventWidgetInstance;
	UPROPERTY(VisibleAnywhere)
	FEventActionInitData EventActionInitData;
};
