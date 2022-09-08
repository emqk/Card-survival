// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardBase.generated.h"

class UFollowComponent;
class UPlayZoneComponent;

UCLASS()
class CARDSURVIVAL_API ACardBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardBase();

	TObjectPtr<UPlayZoneComponent> GetPlayZone() const { return PlayZone; };
	void SetPlayZone(TObjectPtr<UPlayZoneComponent> NewPlayZone) { PlayZone = NewPlayZone; }

	TObjectPtr<UFollowComponent> GetFollowComponent() const { return FollowComponent; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UFollowComponent> FollowComponent;


	// PlayZone in which this card is currently in
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayZoneComponent> PlayZone;

};
