// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardBase.h"
#include "Utils/FollowComponent.h"


ACardBase::ACardBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMeshComponent);


	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}
