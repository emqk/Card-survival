// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OwnPlayerController.h"
#include "Player/PlayerPawn.h"
#include "Player/Cursor.h"


AOwnPlayerController::AOwnPlayerController()
{
	bShowMouseCursor = true;
}

void AOwnPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Cursor3D = GetWorld()->SpawnActor<ACursor>(Params);
}

void AOwnPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (PlayerPawn)
	{
		PlayerPawn->InteractionTick(GetCursor3D());
	}
}

void AOwnPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerPawn = Cast<APlayerPawn>(aPawn);
}

void AOwnPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Primary
	InputComponent->BindAction("Primary", IE_Pressed, this, &AOwnPlayerController::PrimaryInputPressed);
	InputComponent->BindAction("Primary", IE_Released, this, &AOwnPlayerController::PrimaryInputReleased);

	// Secondary
	InputComponent->BindAction("Secondary", IE_Pressed, this, &AOwnPlayerController::SecondaryInputPressed);
	InputComponent->BindAction("Secondary", IE_Released, this, &AOwnPlayerController::SecondaryInputReleased);
}

void AOwnPlayerController::PrimaryInputPressed()
{
	if (PlayerPawn)
	{
		PlayerPawn->PrimaryInputPressed();
	}
}

void AOwnPlayerController::PrimaryInputReleased()
{
	if (PlayerPawn)
	{
		PlayerPawn->PrimaryInputReleased();
	}
}

void AOwnPlayerController::SecondaryInputPressed()
{
	if (PlayerPawn)
	{
		PlayerPawn->SecondaryInputPressed();
	}
}

void AOwnPlayerController::SecondaryInputReleased()
{
	if (PlayerPawn)
	{
		PlayerPawn->SecondaryInputReleased();
	}
}
