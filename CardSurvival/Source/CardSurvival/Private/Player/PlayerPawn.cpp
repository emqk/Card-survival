// Fill out your copyright notice in the Description page of Project Settings.

// Player
#include "Player/PlayerPawn.h"
#include "Player/Cursor.h"
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
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Cursor3D = GetWorld()->SpawnActor<ACursor>(Params);
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Primary
	PlayerInputComponent->BindAction("Primary", IE_Pressed, this, &APlayerPawn::PrimaryInputPressed);
	PlayerInputComponent->BindAction("Primary", IE_Released, this, &APlayerPawn::PrimaryInputReleased);

	// Secondary
	PlayerInputComponent->BindAction("Secondary", IE_Pressed, this, &APlayerPawn::SecondaryInputPressed);
	PlayerInputComponent->BindAction("Secondary", IE_Released, this, &APlayerPawn::SecondaryInputReleased);
}

bool APlayerPawn::IsInteracting() const
{
	return InteractionComponent->IsInteracting();
}

void APlayerPawn::PrimaryInputPressed()
{
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

TObjectPtr<ACursor> APlayerPawn::GetCursor3D() const
{
	return Cursor3D;
}
