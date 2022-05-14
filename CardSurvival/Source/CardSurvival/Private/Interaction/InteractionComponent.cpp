// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FHitResult UInteractionComponent::GetResult()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

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

