// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapNode.h"

AMapNode::AMapNode()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

void AMapNode::AddConnection(AMapNode* Node)
{
	Connections.Add(Node);
}
