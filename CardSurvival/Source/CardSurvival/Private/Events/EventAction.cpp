// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventAction.h"
#include "Events/EventsManager.h"
#include "Player/PlayerSubsystem.h"

void UEventAction::Perform_Implementation()
{
	GetEventsManager()->NextStage(this);
}

AEventsManager* UEventAction::GetEventsManager() const
{
	FWorldContext* WorldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	UWorld* World = WorldContext->World();

	UPlayerSubsystem* PlayerSubsystem = World->GetSubsystem<UPlayerSubsystem>();
	return PlayerSubsystem->GetEventsManager();
}
