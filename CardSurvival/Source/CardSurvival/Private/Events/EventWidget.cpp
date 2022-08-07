// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventWidget.h"

void UEventWidget::Display_Implementation(UEventData* NewEventData)
{
	EventData = NewEventData;
}

void UEventWidget::GoToFirstStage()
{
	CurrentStage = -1;
	NextStage();
}

void UEventWidget::NextStage()
{
	CurrentStage++;
	OnNextStageOpen(CurrentStage);
}
