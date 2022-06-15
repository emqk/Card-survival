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
class ACursor;

UCLASS()
class CARDSURVIVAL_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsInteracting() const;

	const FHitResult& GetHitResult() const { return HitResult; };
	TObjectPtr<ACursor> GetCursor3D() const;


private:
	
	void PrimaryInputPressed();
	void PrimaryInputReleased();
	void SecondaryInputPressed();
	void SecondaryInputReleased();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UInteractionComponent> InteractionComponent;

	
	// Cached interaction hit actor
	UPROPERTY();
	TObjectPtr<AActor> HitActor = nullptr;
	UPROPERTY();
	FHitResult HitResult;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACursor> Cursor3D;
};
