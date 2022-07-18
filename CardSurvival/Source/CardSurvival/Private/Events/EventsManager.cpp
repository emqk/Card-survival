// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventsManager.h"
#include "Player/PlayerSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Events/EventWidget.h"

AEventsManager::AEventsManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AEventsManager::BeginPlay()
{
	UPlayerSubsystem* PlayerSubsystem = GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
	PlayerSubsystem->SetEventsManager(this);
}

void AEventsManager::StartEvent(UEventData* EventData)
{
	if (!EventWidgetInstance)
	{
		if (!EventWidgetClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot start event - widget class is null!"))
			return;
		}

		EventWidgetInstance = CreateWidget<UEventWidget>(GetWorld(), EventWidgetClass);
	}

	EventWidgetInstance->ShowEvents(EventData);
	EventWidgetInstance->AddToViewport();
}

void AEventsManager::EndEvent()
{
	EventWidgetInstance->RemoveFromViewport();
}
