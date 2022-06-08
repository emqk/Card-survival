// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/FollowComponent.h"

UFollowComponent::UFollowComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Test from time to time if there isn't too many ticks. Maybe replace logs with draw debug
	//UE_LOG(LogTemp, Warning, TEXT("Tick!"))

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = FollowLocation;

	// If Follow actor exists, follow it and treat TargetLocation as an offset
	if (FollowActor)
	{
		TargetLocation += FollowActor->GetActorLocation();
	}

	FVector NewLocation = FMath::Lerp(CurrentLocation, FVector(TargetLocation), FollowSpeed * DeltaTime);

	// Snap and disable tick if new location is close enough to the target
	if (bTryDisableTick)
	{
		float DistanceFromTarget = FVector::Dist(NewLocation, TargetLocation);
		if (DistanceFromTarget <= SnapDistance)
		{
			GetOwner()->SetActorLocation(TargetLocation);
			SetComponentTickEnabled(false);
			SetTryDisableTick(false);
			return;
		}
	}

	GetOwner()->SetActorLocation(NewLocation);
}

void UFollowComponent::SetFollow(TObjectPtr<AActor> NewFollowActor, const FVector& NewFollowLocation, bool TryDisableTick /* = true */)
{
	FollowActor = NewFollowActor;
	FollowLocation = NewFollowLocation;

	SetComponentTickEnabled(true);
	SetTryDisableTick(TryDisableTick);
}
