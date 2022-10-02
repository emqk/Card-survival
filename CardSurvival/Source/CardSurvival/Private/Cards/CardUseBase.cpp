// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardUseBase.h"
#include "Cards/CardBase.h"
#include "Board/PlayZoneComponent.h"

void UCardUseBase::Use_Implementation(ACardBase* From, ACardBase* To)
{
	if (!From || !To)
	{
		return;
	}

	From->DestroyMe();
	To->DestroyMe();
}

bool UCardUseBase::IsCardAccepted(UCardData* CardData)
{
	return AcceptedCards.Contains(CardData);
}
