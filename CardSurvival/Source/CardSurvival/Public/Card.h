// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

class UTextRenderComponent;

UCLASS()
class CARDSURVIVAL_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	ACard();


protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* NameTextComponent;
};
