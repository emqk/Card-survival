// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::StartInteraction(IInteractable* Interactable, EInteractionType InteractionType)
{
	// End interaction with cached interactable (if there is any)
	if (InteractableTarget)
		EndInteraction();

	// Set new interactable
	InteractableTarget.SetInterface(Interactable);
	InteractableTarget.SetObject(Interactable->_getUObject());

	// Start interaction
	IInteractable::Execute_StartInteraction(InteractableTarget.GetObject(), GetOwner(), InteractionType);
}

void UInteractionComponent::TickInteraction()
{
	if(InteractableTarget)
	{
		IInteractable::Execute_TickInteraction(InteractableTarget.GetObject(), GetOwner());
	}
}

void UInteractionComponent::EndInteraction()
{
	if (InteractableTarget)
	{
		IInteractable::Execute_EndInteraction(InteractableTarget.GetObject(), GetOwner());
		InteractableTarget = nullptr; // null because we no longer need a reference to (old) interactable
	}
}

FHitResult UInteractionComponent::GetResult()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		FVector Location;
		FVector Direction;
		PlayerController->DeprojectMousePositionToWorld(Location, Direction);

		ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
		FHitResult Result;
		GetWorld()->LineTraceSingleByChannel(Result, Location, Direction * InteractionDistance, Channel);

		return Result;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player controller is null!"))
	}

	return FHitResult();
}

