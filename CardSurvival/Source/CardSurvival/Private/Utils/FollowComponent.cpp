// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/FollowComponent.h"

UFollowComponent::UFollowComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Follower)
	{
		FVector CurrentLocation = Follower->GetActorLocation();
		FVector NewLocation = FMath::Lerp(CurrentLocation, FVector(FollowLocation), FollowSpeed * DeltaTime);

		Follower->SetActorLocation(NewLocation);
	}
}

void UFollowComponent::SetFollower(AActor* NewFollower)
{
	Follower = NewFollower;
}

void UFollowComponent::SetFollowLocation(const FVector& NewFollowLocation)
{
	FollowLocation = NewFollowLocation;
}

