// Fill out your copyright notice in the Description page of Project Settings.

// Player
#include "PlayerPawn.h"
#include "Interaction/InteractionComponent.h"
#include "Utils/FollowComponent.h"

// Engine
#include "Camera/CameraComponent.h" 
#include "DrawDebugHelpers.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InteractionComponent)
	{
		FHitResult HitResult = InteractionComponent->GetResult();
		if (HitResult.bBlockingHit)
		{
			HitActor = HitResult.GetActor();
			DrawDebugSphere(GetWorld(), HitResult.Location, 50, 10, FColor::Red, false, -1.0f, 0, 5);	
		}

		InteractionComponent->TickInteraction();
		FollowComponent->SetFollowLocation(HitResult.Location + CardHoldHeightOffset);
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Primary", IE_Pressed, this, &APlayerPawn::PrimaryInputPressed);
	PlayerInputComponent->BindAction("Primary", IE_Released, this, &APlayerPawn::PrimaryInputReleased);
}

void APlayerPawn::PrimaryInputPressed()
{
	if (HitActor)
	{
		IInteractable* Interactable = Cast<IInteractable>(HitActor);
		if (Interactable)
		{
			InteractionComponent->StartInteraction(Interactable);
		}
	}
}

void APlayerPawn::PrimaryInputReleased()
{
	InteractionComponent->EndInteraction();
}

