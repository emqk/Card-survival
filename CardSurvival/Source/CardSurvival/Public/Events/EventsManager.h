// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventsManager.generated.h"

class UEventWidget;
class UEventData;

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



protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEventWidget> EventWidgetClass;
	UPROPERTY(VisibleAnywhere)
	UEventWidget* EventWidgetInstance;
};
