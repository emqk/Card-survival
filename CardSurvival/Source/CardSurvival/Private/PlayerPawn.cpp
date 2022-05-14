// Fill out your copyright notice in the Description page of Project Settings.

// Player
#include "PlayerPawn.h"
#include "Interaction/InteractionComponent.h"

// Engine
#include "Camera/CameraComponent.h" 
#include "DrawDebugHelpers.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InteractionComponent)
	{
		FHitResult HitResult = InteractionComponent->GetResult();
		if (HitResult.bBlockingHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.Location, 111, 10, FColor::Red, false, -1.0f, 0, 5);	
		}
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

