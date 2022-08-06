// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventAction.h"
#include "Events/EventsManager.h"
#include "Player/PlayerSubsystem.h"

void UEventAction::Perform_Implementation()
{
	GetEventsManager()->NextStage();
}

AEventsManager* UEventAction::GetEventsManager() const
{
	return GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetEventsManager();
}
