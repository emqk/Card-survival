// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerSubsystem.h"
#include "Player/PlayerPawn.h"
#include "Utils/FollowComponent.h"

#include "Kismet/GameplayStatics.h"


APlayerPawn* UPlayerSubsystem::GetPlayerPawn() const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerPawn* Player = Cast<APlayerPawn>(PlayerController->GetPawn());

	return Player;
}

ACursor* UPlayerSubsystem::GetPlayerCursor3D() const
{
	return GetPlayerCursor3D(GetPlayerPawn());
}

ACursor* UPlayerSubsystem::GetPlayerCursor3D(const APlayerPawn* PlayerPawn) const
{
	return PlayerPawn->GetCursor3D();
}
