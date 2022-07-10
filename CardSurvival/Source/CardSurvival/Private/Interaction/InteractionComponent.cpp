// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"
#include "Player/OwnPlayerController.h"
#include "Player/PlayerSubsystem.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::StartInteraction(IInteractable* Interactable, EInteractionType InteractionType)
{
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
		bool bResult = IInteractable::Execute_TickInteraction(InteractableTarget.GetObject(), GetOwner());
		IInteractable::Execute_OnTickInteractionEnd(InteractableTarget.GetObject(), GetOwner(), bResult);
		if (bResult)
		{
			EndInteraction();
		}
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

void UInteractionComponent::StartSelect(IInteractable* Interactable)
{
	// End selection of cached interactable (if there is any)
	if (SelectTarget)
		EndSelect();

	// Set new interactable
	SelectTarget.SetInterface(Interactable);
	SelectTarget.SetObject(Interactable->_getUObject());

	// Start selection
	IInteractable::Execute_StartSelect(SelectTarget.GetObject(), GetOwner());
}

void UInteractionComponent::TickSelect()
{
	if (SelectTarget)
	{
		IInteractable::Execute_TickSelect(SelectTarget.GetObject(), GetOwner());
	}
}

void UInteractionComponent::EndSelect()
{
	if (SelectTarget)
	{
		IInteractable::Execute_EndSelect(SelectTarget.GetObject(), GetOwner());
		SelectTarget = nullptr; // null because we no longer need a reference to (old) interactable
	}
}

FHitResult UInteractionComponent::GetResult()
{
	AOwnPlayerController* PlayerController = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerController();

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

bool UInteractionComponent::IsActorSelected(AActor* Actor) const
{
	return Actor == SelectTarget.GetObject();
}

bool UInteractionComponent::IsInteracting() const
{
	return InteractableTarget != nullptr;
}

