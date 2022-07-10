// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Own
#include "PlayerPawn.generated.h"

class UCameraComponent;
class UInteractionComponent;
class UFollowComponent;

UCLASS()
class CARDSURVIVAL_API APlayerPawn : public APawn
{
	GENERATED_BODY()
	
	friend class AOwnPlayerController;

public:
	APlayerPawn();

	bool IsInteracting() const;
	const FHitResult& GetHitResult() const { return HitResult; };

protected:
	void InteractionTick(AActor* Cursor3D);

private:
	
	void PrimaryInputPressed();
	void PrimaryInputReleased();
	void SecondaryInputPressed();
	void SecondaryInputReleased();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UInteractionComponent> InteractionComponent;

	// Cached interaction hit actor
	UPROPERTY();
	TObjectPtr<AActor> HitActor = nullptr;
	UPROPERTY();
	FHitResult HitResult;
};
