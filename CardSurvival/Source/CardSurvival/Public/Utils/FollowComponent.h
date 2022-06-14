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

	void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetFollow(TObjectPtr<AActor> NewFollowActor, const FVector& NewFollowLocation, const FRotator& NewRotation, bool TryDisableTick = true);
	void SetFollowRotation(const FRotator& NewRotation, bool TryDisableTick = true);
	void SetAdditionalOffset(const FVector& Offset, bool TryDisableTick = true);
	void RemoveAdditionalOffset();

protected:
	void SetTryDisableTick(bool TryDisableTick) { bTryDisableTick = TryDisableTick; };


protected:
	UPROPERTY(EditDefaultsOnly)
	float FollowSpeed = 15;
	// Snap to the target (and possibly disable tick) if the distance is equal/smaller than this value
	UPROPERTY(VisibleAnywhere)
	float SnapDistance = 0.1f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> FollowActor;
	UPROPERTY(VisibleAnywhere)
	FVector FollowLocation;
	UPROPERTY(VisibleAnywhere)
	FRotator FollowRotation;
	UPROPERTY(VisibleAnywhere)
	FVector AdditionalOffset;

private:
	bool bTryDisableTick = false;
};
