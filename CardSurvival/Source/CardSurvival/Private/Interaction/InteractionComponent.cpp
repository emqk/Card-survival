// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"
#include "Interaction/InteractionAim.h"
#include "Player/OwnPlayerController.h"
#include "Player/PlayerSubsystem.h"
#include "Cards/CardBase.h"

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

	TickAim();
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
	UPlayerSubsystem* PlayerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
	AOwnPlayerController* PlayerController = PlayerSubsystem->GetPlayerController();

	if (PlayerController)
	{
		FHitResult Result;
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Result);

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

void UInteractionComponent::TickAim()
{
	if(!InteractionAimInstance)
		return;

	UPlayerSubsystem* PlayerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
	const FHitResult& HitResult = PlayerSubsystem->GetHitResultUnderCursor();

	InteractionAimInstance->UpdateEnd(HitResult.Location);
}

AActor* UInteractionComponent::GetAimStart() const
{
	if (!InteractionAimInstance)
	{
		return nullptr;
	}

	return InteractionAimInstance->GetAimStart();
}

AInteractionAim* UInteractionComponent::GetInteractionAim(AActor* Start)
{
	if (!Start)
	{
		return nullptr;
	}

	if (InteractionAimInstance)
	{
		return InteractionAimInstance;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform Transform;
	InteractionAimInstance = Cast<AInteractionAim>(GetWorld()->SpawnActor(InteractionAimClass, &Transform, Params));
	InteractionAimInstance->Init(Start, Start->GetActorLocation() + FVector(1500, 0, 0));

	return InteractionAimInstance;
}

void UInteractionComponent::DestroyInteractionAim()
{
	if (!InteractionAimInstance)
	{
		return;
	}

	InteractionAimInstance->Destroy();
	InteractionAimInstance = nullptr;
}
