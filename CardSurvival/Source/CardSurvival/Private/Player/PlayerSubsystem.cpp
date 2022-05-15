// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerSubsystem.h"
#include "PlayerPawn.h"
#include "Utils/FollowComponent.h"

#include "Kismet/GameplayStatics.h"


APlayerPawn* UPlayerSubsystem::GetPlayerPawn() const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerPawn* Player = Cast<APlayerPawn>(PlayerController->GetPawn());

	return Player;
}

UFollowComponent* UPlayerSubsystem::GetPlayerFollowComponent() const
{
	APlayerPawn* Player = GetPlayerPawn();
	UFollowComponent* FollowComp = Cast<UFollowComponent>(Player->GetComponentByClass(UFollowComponent::StaticClass()));

	return FollowComp;
}
