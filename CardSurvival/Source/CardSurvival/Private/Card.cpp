// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "Utils/FollowComponent.h"
#include "Player/PlayerSubsystem.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);
	NameTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameText"));
	NameTextComponent->SetupAttachment(BaseMeshComponent);
}

bool ACard::StartInteraction_Implementation(AActor* Interactor)
{		
	UFollowComponent* FollowComp = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerFollowComponent();
	FollowComp->SetFollower(this);

	return true;
}

bool ACard::TickInteraction_Implementation(AActor* Interactor)
{
	return true;
}

bool ACard::EndInteraction_Implementation(AActor* Interactor)
{
	return true;
}
