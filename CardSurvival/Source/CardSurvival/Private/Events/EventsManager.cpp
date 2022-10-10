// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventsManager.h"
#include "Player/PlayerSubsystem.h"
#include "Player/OwnPlayerController.h"
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

bool AEventsManager::TryStartRandomEvent()
{
	UEventData* EventData = GetRandomEventData();
	if (!EventData)
	{
		return false;
	}

	if (!EventWidgetInstance)
	{
		if (!EventWidgetClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot start event - widget class is null!"))
			return false;
		}

		EventWidgetInstance = CreateWidget<UEventWidget>(GetWorld(), EventWidgetClass);
	}

	EventWidgetInstance->Display(EventData);
	EventWidgetInstance->AddToViewport();

	// Enable UI input
	AOwnPlayerController* PlayerController = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerController();
	FInputModeUIOnly InputData;
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputData);

	return true;
}

void AEventsManager::NextStage()
{
	if (!EventWidgetInstance)
	{
		return;
	}

	EventWidgetInstance->NextStage();

	if (EventWidgetInstance->ShouldEnd())
	{
		EndEvent();
	}
}

void AEventsManager::EndEvent()
{
	EventWidgetInstance->RemoveFromViewport();

	// Enable 3D game input
	AOwnPlayerController* PlayerController = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerController();
	FInputModeGameAndUI InputData;
	InputData.SetHideCursorDuringCapture(false);
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputData.SetWidgetToFocus(nullptr);
	PlayerController->SetInputMode(InputData);
}

UEventData* AEventsManager::GetRandomEventData() const
{
	int32 ShouldDisplayEventInt = FMath::RandRange(1, 100);
	bool bShouldDisplayEvent = ShouldDisplayEventInt <= ChanceToStartEvent;
	UE_LOG(LogTemp, Warning, TEXT("ShouldDisplayEvent %i"), ShouldDisplayEventInt)
	if (!bShouldDisplayEvent || EventDatas.Num() <= 0)
	{
		return nullptr;
	}

	int32 Index = FMath::RandRange(0, EventDatas.Num() - 1);
	return EventDatas[Index];
}
