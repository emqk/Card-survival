// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBoardPawn.h"
#include "Player/PlayerSubsystem.h"

#include "Camera/CameraComponent.h" 

APlayerBoardPawn::APlayerBoardPawn()
{
}

void APlayerBoardPawn::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UPlayerSubsystem>()->SetBoardPlayer(this);
}
