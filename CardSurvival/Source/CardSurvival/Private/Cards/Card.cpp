// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"
#include "Cards/CardData.h"
#include "Cards/CardInfoWidget.h"
#include "Tokens/TokenRow.h"
#include "Board/PlayZoneComponent.h"
#include "Utils/FollowComponent.h"
#include "Utils/Statistic.h"
#include "Utils/ParallaxData.h"
#include "Player/PlayerSubsystem.h"
#include "Player/Cursor.h"

#include "Components/WidgetComponent.h"



ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);

	InfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidgetComponent->SetCollisionProfileName("NoCollision");
	InfoWidgetComponent->SetupAttachment(BaseMeshComponent);

	ProgressBarMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProgressBar"));
	ProgressBarMeshComponent->SetCastShadow(false);
	ProgressBarMeshComponent->SetComponentTickEnabled(false);
	ProgressBarMeshComponent->SetupAttachment(BaseMeshComponent);


	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}

void ACard::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerSubsystem();
	ProgressBarMeshComponent->SetVisibility(false);
}

void ACard::ApplyCardData()
{
	if (CardData && CardData->GetParalaxData())
	{
		UParallaxData* ParallaxData = CardData->GetParalaxData();

		// Widget
		UCardInfoWidget* InfoWidget = Cast<UCardInfoWidget>(InfoWidgetComponent->GetWidget());
		if (InfoWidget)
		{
			InfoWidget->Refresh(CardData);
		}

		// Material
		UMaterialInstanceDynamic* MaterialInstance = BaseMeshComponent->CreateDynamicMaterialInstance(2);
		MaterialInstance->SetTextureParameterValue(FName("Base Image"), ParallaxData->GetBaseTexture());
		MaterialInstance->SetTextureParameterValue(FName("ZDepthMap"), ParallaxData->GetDepthTexture());
	}
}

void ACard::SetPlayerSubsystem()
{
	PlayerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
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

		ACursor* Cursor3D = GetPlayerSubsystem()->GetPlayerCursor3D();
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
		ATokenRow* TokenRow = GetPlayerSubsystem()->GetTokenRow();
		for (const FTokenDataInstance& DataInstance : CardData->GetStatuses())
		{
			TokenRow->AddTokens(DataInstance.TokenData, DataInstance.Amount);
		}
	}
}

bool ACard::EndInteraction_Implementation(AActor* Interactor)
{
	if (CurrentInteractionType == EInteractionType::Primary)
	{
		SetActorEnableCollision(true);

		FVector CurrentLocation = GetActorLocation();

		// Add this Card to the PlayZone if available
		const FHitResult& HitResult = GetPlayerSubsystem()->GetHitResultUnderCursor();
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		UPlayZoneComponent* HitPlayZone = Cast<UPlayZoneComponent>(HitComponent);

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
	bool PlayerInteracting = GetPlayerSubsystem()->IsPlayerInteracting();
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
	bool PlayerInteracting = GetPlayerSubsystem()->IsPlayerInteracting();
	if (!PlayerInteracting)
	{
		FVector CurrentLocation = GetActorLocation();
		FollowComponent->RemoveAdditionalOffset();
		FollowComponent->SetFollowRotation(FRotator(0, 0, 0));
	}

	return true;
}
