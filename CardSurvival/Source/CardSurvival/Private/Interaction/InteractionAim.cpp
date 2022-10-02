// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionAim.h"

AInteractionAim::AInteractionAim()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

void AInteractionAim::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractionAim::Init(AActor* StartActor, const FVector& NewEnd)
{
	Start = StartActor;
	End = NewEnd;

	RefreshMesh();
}

void AInteractionAim::UpdateEnd(const FVector& NewEnd)
{
	End = NewEnd;

	RefreshMesh();
}
