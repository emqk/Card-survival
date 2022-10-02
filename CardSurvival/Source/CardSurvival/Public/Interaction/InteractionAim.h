// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionAim.generated.h"

class ACardBase;

UCLASS()
class CARDSURVIVAL_API AInteractionAim : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractionAim();

	virtual void BeginPlay() override;

	void Init(AActor* StartActor, const FVector& NewEnd);
	void UpdateEnd(const FVector& NewEnd);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshMesh();

	AActor* GetAimStart() const { return Start; };

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector End;
};
