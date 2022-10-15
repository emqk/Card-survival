// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Events/EventData.h"
#include "GameFramework/Actor.h"
#include "EventsManager.generated.h"

class UEventWidget;
class UEventData;
class UStatistic;
class UEndGameWidget;

UCLASS()
class CARDSURVIVAL_API AEventsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEventsManager();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool TryStartRandomEvent();
	UFUNCTION(BlueprintCallable)
	void NextStage(UEventAction* EventAction);
	UFUNCTION(BlueprintCallable)
	void EndEvent();

	UFUNCTION()
	void CheckEndGame(UStatistic* Health);
	void EndGame(bool bVictory);

	UFUNCTION(BlueprintCallable)
	UEventData* GetRandomEventData() const;

	UFUNCTION(BlueprintCallable)
	void SetEventActionInitData(const FEventActionInitData& NewEventActionInitData) { EventActionInitData = NewEventActionInitData; }
	UFUNCTION(BlueprintCallable)
	FEventActionInitData GetEventActionInitData() const { return EventActionInitData; };

protected:
	void SetUIInputActive(bool bActive);

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UEventData*> EventDatas;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEventWidget> EventWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UEventWidget* EventWidgetInstance;
	UPROPERTY(VisibleAnywhere)
	FEventActionInitData EventActionInitData;
	UPROPERTY(BlueprintReadOnly)
	UEventAction* LastEventAction;

	UPROPERTY(EditDefaultsOnly)
	int32 ChanceToStartEvent = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundBase* StartEventSound;

	// EndGame
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEndGameWidget> EndGameWidgetClass;
};
