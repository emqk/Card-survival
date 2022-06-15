// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"
#include "Components/TextRenderComponent.h"
#include "Utils/FollowComponent.h"
#include "Utils/Statistic.h"
#include "Board/PlayZone.h"
#include "Player/PlayerSubsystem.h"
#include "Player/Cursor.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);
	NameTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameText"));
	NameTextComponent->SetupAttachment(BaseMeshComponent);
	StrengthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("StrengthText"));
	StrengthTextComponent->SetupAttachment(BaseMeshComponent);
	ProgressBarMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProgressBar"));
	ProgressBarMeshComponent->SetCastShadow(false);
	ProgressBarMeshComponent->SetComponentTickEnabled(false);
	ProgressBarMeshComponent->SetupAttachment(BaseMeshComponent);

	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}

void ACard::BeginPlay()
{
	Super::BeginPlay();

	ProgressBarMeshComponent->SetVisibility(false);
}

bool ACard::StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType)
{		
	CurrentInteractionType = InteractionType;

	if (InteractionType == EInteractionType::Primary)
	{
		SetActorEnableCollision(false);

		if (PlayZone)
		{
			PlayZone->RemoveCard(this);
		}

		ACursor* Cursor3D = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerCursor3D();
		FollowComponent->SetFollow(Cursor3D, HoldHeightOffset, FRotator(), false);
	}
	else if (InteractionType == EInteractionType::Secondary)
	{
		ProgressBarMeshComponent->SetVisibility(true);
	}

	return true;
}

bool ACard::TickInteraction_Implementation(AActor* Interactor)
{
	if (CurrentInteractionType == EInteractionType::Secondary)
	{		
		float Delta = GetWorld()->GetDeltaSeconds();
		Progress->ChangeByAmount(Delta * 5.0f);

		FVector CurrentBarScale = ProgressBarMeshComponent->GetComponentScale();
		ProgressBarMeshComponent->SetWorldScale3D(FVector(CurrentBarScale.X, Progress->GetAmount(), CurrentBarScale.Z));

		return Progress->IsMax();
	}

	return false;
}

void ACard::OnTickInteractionEnd_Implementation(AActor* Interactor, bool TickEndResult)
{
	if (TickEndResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("Completed!"))
	}
}

bool ACard::EndInteraction_Implementation(AActor* Interactor)
{
	if (CurrentInteractionType == EInteractionType::Primary)
	{
		SetActorEnableCollision(true);

		FVector CurrentLocation = GetActorLocation();

		// Add this Card to the PlayZone if available
		const FHitResult& HitResult = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetHitResultUnderCursor();
		AActor* HitActor = HitResult.GetActor();
		APlayZone* HitPlayZone = Cast<APlayZone>(HitActor);

		if (HitPlayZone)
		{
			HitPlayZone->AddCard(this);
		}
		else
		{
			FollowComponent->SetFollow(nullptr, FVector(CurrentLocation.X, CurrentLocation.Y, 0), FRotator());
		}

		// Sometimes EndSelect is not called. Removing additional offset to fix it
		FollowComponent->RemoveAdditionalOffset();
	}
	else if (CurrentInteractionType == EInteractionType::Secondary)
	{
		ProgressBarMeshComponent->SetVisibility(false);
		Progress->SetToMin();
	}

	return true;
}

bool ACard::StartSelect_Implementation(AActor* Interactor)
{
	bool PlayerInteracting = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->IsPlayerInteracting();
	if (!PlayerInteracting)
	{
		FVector CurrentLocation = GetActorLocation();
		FollowComponent->SetAdditionalOffset(FVector(0, 0, 100));
		FollowComponent->SetFollowRotation(FRotator(25.0f, 0, 0));
	}

	return true;
}

bool ACard::TickSelect_Implementation(AActor* Interactor)
{	
	return true;
}

bool ACard::EndSelect_Implementation(AActor* Interactor)
{
	bool PlayerInteracting = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->IsPlayerInteracting();
	if (!PlayerInteracting)
	{
		FVector CurrentLocation = GetActorLocation();
		FollowComponent->RemoveAdditionalOffset();
		FollowComponent->SetFollowRotation(FRotator(0, 0, 0));
	}

	return true;
}
