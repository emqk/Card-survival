// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Interactable.h"


bool IInteractable::CanInteract_Implementation(EInteractionType InteractionType)
{
	return true;
}

bool IInteractable::CanSelect_Implementation(AActor* Interactor)
{
	return true;
}
