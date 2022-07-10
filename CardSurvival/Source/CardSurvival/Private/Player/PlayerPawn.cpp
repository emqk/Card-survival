// Fill out your copyright notice in the Description page of Project Settings.

// Player
#include "Player/PlayerPawn.h"
#include "Interaction/InteractionComponent.h"
#include "Utils/FollowComponent.h"
#include "Player/PlayerSubsystem.h"

// Engine
#include "Camera/CameraComponent.h" 
#include "DrawDebugHelpers.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

bool APlayerPawn::IsInteracting() const
{
	return InteractionComponent->IsInteracting();
}

void APlayerPawn::PrimaryInputPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("aaaaa"))
	if (HitActor)
	{
		IInteractable* Interactable = Cast<IInteractable>(HitActor);
		if (Interactable)
		{
			InteractionComponent->StartInteraction(Interactable, EInteractionType::Primary);
		}
	}
}

void APlayerPawn::PrimaryInputReleased()
{
	InteractionComponent->EndInteraction();
}

void APlayerPawn::SecondaryInputPressed()
{
	if (HitActor)
	{
		IInteractable* Interactable = Cast<IInteractable>(HitActor);
		if (Interactable)
		{
			InteractionComponent->StartInteraction(Interactable, EInteractionType::Secondary);
		}
	}
}

void APlayerPawn::SecondaryInputReleased()
{
	InteractionComponent->EndInteraction();
}

void APlayerPawn::InteractionTick(AActor* Cursor3D)
{
	if (InteractionComponent)
	{
		HitResult = InteractionComponent->GetResult();
		if (HitResult.bBlockingHit)
		{
			HitActor = HitResult.GetActor();
			DrawDebugSphere(GetWorld(), HitResult.Location, 50, 10, FColor::Red, false, -1.0f, 0, 5);
		}

		// Select
		IInteractable* Interactable = Cast<IInteractable>(HitActor);
		if (Interactable)
		{
			if (!InteractionComponent->IsActorSelected(HitResult.GetActor()))
			{
				InteractionComponent->StartSelect(Interactable);
			}
			else
			{
				InteractionComponent->TickSelect();
			}
		}
		else
		{
			InteractionComponent->EndSelect();
		}

		InteractionComponent->TickInteraction();
		Cursor3D->SetActorLocation(HitResult.Location);
	}
}
