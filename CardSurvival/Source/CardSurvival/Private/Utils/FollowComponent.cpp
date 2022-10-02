// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/FollowComponent.h"

UFollowComponent::UFollowComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UFollowComponent::BeginPlay()
{
	Super::BeginPlay();

	FollowLocation = GetOwner()->GetActorLocation();
}

void UFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Test from time to time if there isn't too many ticks. Maybe replace logs with draw debug
	//UE_LOG(LogTemp, Warning, TEXT("Tick!"))

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = FollowLocation + AdditionalOffset;

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator TargetRotation = FollowRotation;

	// If Follow actor exists, follow it and treat TargetLocation as an offset
	if (FollowActor)
	{
		TargetLocation += FollowActor->GetActorLocation();
	}

	// Calculate new location and rotation
	float Delta = FMath::Clamp(FollowSpeed * DeltaTime, 0.0f, 1.0f);
	FVector NewLocation = FMath::Lerp(CurrentLocation, TargetLocation, Delta);
	FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, Delta);

	// Snap and disable tick if new location is close enough to the target
	if (bTryDisableTick)
	{
		float DistanceFromTarget = FVector::Dist(NewLocation, TargetLocation);
		if (DistanceFromTarget <= SnapDistance)
		{
			GetOwner()->SetActorLocation(TargetLocation);
			GetOwner()->SetActorRotation(TargetRotation);
			SetComponentTickEnabled(false);
			SetTryDisableTick(false);
			return;
		}
	}

	GetOwner()->SetActorLocation(NewLocation);
	GetOwner()->SetActorRotation(NewRotation);
}

void UFollowComponent::SetFollow(TObjectPtr<AActor> NewFollowActor, const FVector& NewFollowLocation, const FRotator& NewRotation, bool TryDisableTick /* = true */)
{
	FollowActor = NewFollowActor;
	FollowLocation = NewFollowLocation;
	FollowRotation = NewRotation;

	SetComponentTickEnabled(true);
	SetTryDisableTick(TryDisableTick);
}

void UFollowComponent::SetFollowRotation(const FRotator& NewRotation, bool TryDisableTick /* = true */)
{
	FollowRotation = NewRotation;

	SetComponentTickEnabled(true);
	SetTryDisableTick(TryDisableTick);
}

void UFollowComponent::SetAdditionalOffset(const FVector& Offset, bool TryDisableTick /* = true */)
{
	AdditionalOffset = Offset;

	SetComponentTickEnabled(true);
	SetTryDisableTick(TryDisableTick);
}

void UFollowComponent::RemoveAdditionalOffset()
{
	AdditionalOffset = FVector(0, 0, 0);
}
