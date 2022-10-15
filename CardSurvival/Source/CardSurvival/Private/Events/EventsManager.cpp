// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventsManager.h"
#include "Player/PlayerSubsystem.h"
#include "Player/OwnPlayerController.h"
#include "Player/PlayerInventorySubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Events/EventWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Statistic.h"
#include "World/EndGameWidget.h"

AEventsManager::AEventsManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AEventsManager::BeginPlay()
{
	UPlayerSubsystem* PlayerSubsystem = GetWorld()->GetSubsystem<UPlayerSubsystem>();
	PlayerSubsystem->SetEventsManager(this);

	UPlayerInventorySubsystem* PlayerInventory = GetWorld()->GetSubsystem<UPlayerInventorySubsystem>();
	PlayerInventory->GetHealth()->OnAttributeChange.AddUniqueDynamic(this, &AEventsManager::CheckEndGame);

	SetUIInputActive(false);
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

	SetUIInputActive(true);

	UGameplayStatics::PlaySound2D(GetWorld(), StartEventSound);

	return true;
}

void AEventsManager::NextStage(UEventAction* EventAction)
{
	if (!EventWidgetInstance)
	{
		return;
	}

	LastEventAction = EventAction;
	EventWidgetInstance->NextStage();

	if (EventWidgetInstance->ShouldEnd())
	{
		EndEvent();
	}
}

void AEventsManager::EndEvent()
{
	EventWidgetInstance->RemoveFromViewport();
	SetUIInputActive(false);
}

void AEventsManager::CheckEndGame(UStatistic* Health)
{
	if (Health->GetAmount() <= 0)
	{
		EndGame(false);
	}
}

void AEventsManager::EndGame(bool bVictory)
{
	UEndGameWidget* EndGameWidgetInstance = CreateWidget<UEndGameWidget>(GetWorld(), EndGameWidgetClass);
	EndGameWidgetInstance->Refresh(bVictory);
	EndGameWidgetInstance->AddToViewport();

	SetUIInputActive(true);
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

void AEventsManager::SetUIInputActive(bool bActive)
{
	if (bActive)
	{
		AOwnPlayerController* PlayerController = GetWorld()->GetSubsystem<UPlayerSubsystem>()->GetPlayerController();
		FInputModeUIOnly InputData;
		InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputData);
	}
	else
	{
		AOwnPlayerController* PlayerController = GetWorld()->GetSubsystem<UPlayerSubsystem>()->GetPlayerController();
		FInputModeGameAndUI InputData;
		InputData.SetHideCursorDuringCapture(false);
		InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputData.SetWidgetToFocus(nullptr);
		PlayerController->SetInputMode(InputData);
	}
}
