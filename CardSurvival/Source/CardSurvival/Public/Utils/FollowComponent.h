// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDSURVIVAL_API UFollowComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFollowComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetFollower(AActor* NewFollower);
	void SetFollowLocation(const FVector& NewFollowLocation);


protected:
	UPROPERTY(EditDefaultsOnly)
	float FollowSpeed = 15;

	UPROPERTY(VisibleAnywhere)
	AActor* Follower;
	UPROPERTY(VisibleAnywhere)
	FVector FollowLocation;
};
