// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"
#include "Cards/CardDummy.h"
#include "Cards/CardData.h"
#include "Cards/CardUseBase.h"
#include "Cards/CardInfoWidget.h"
#include "Cards/CardSettings.h"
#include "Cards/CardManager.h"
#include "Tokens/TokenRow.h"
#include "Board/PlayZoneComponent.h"
#include "Utils/FollowComponent.h"
#include "Player/PlayerSubsystem.h"
#include "Player/Cursor.h"
#include "Interaction/InteractionComponent.h"

#include "Components/WidgetComponent.h"


ACard::ACard()
{
	InfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidgetComponent->SetCollisionProfileName("NoCollision");
	InfoWidgetComponent->SetupAttachment(BaseMeshComponent);

	ProgressBarMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProgressBar"));
	ProgressBarMeshComponent->SetCastShadow(false);
	ProgressBarMeshComponent->SetComponentTickEnabled(false);
	ProgressBarMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ACard::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerSubsystem();
	ProgressBarMeshComponent->SetVisibility(false);

	BorderDynamicMaterialInstance = BaseMeshComponent->CreateDynamicMaterialInstance(0);
	BackgroundDynamicMaterialInstance = BaseMeshComponent->CreateDynamicMaterialInstance(1);
	ItemTextureMaterialInstance = BaseMeshComponent->CreateDynamicMaterialInstance(2);
}

bool ACard::CanSelect_Implementation(AActor* Interactor)
{
	return CanInteractAim();
}

void ACard::SetCardData(UCardData* NewCardData)
{
	CardData = NewCardData;
	ApplyCardData();
}

void ACard::ApplyCardData()
{
	if (CardData)
	{
		// Widget
		UCardInfoWidget* InfoWidget = Cast<UCardInfoWidget>(InfoWidgetComponent->GetWidget());
		if (InfoWidget)
		{
			InfoWidget->Refresh(CardData);
		}

		// Material parameters
		ApplyCardDataVisuals();
	}
}

void ACard::ApplyCardDataVisuals()
{
	// Item texture
	if (ItemTextureMaterialInstance)
	{
		ItemTextureMaterialInstance->SetTextureParameterValue(FName("Base Image"), CardData->GetBaseTexture());
		ItemTextureMaterialInstance->SetTextureParameterValue(FName("ZDepthMap"), CardData->GetDepthTexture());
	}

	// Border and Background
	ACardManager* CardManager = PlayerSubsystem->GetCardManager();
	if (CardManager)
	{
		UCardSettings* CardsSettings = CardManager->GetCardsSettings();

		if (CardsSettings && BorderDynamicMaterialInstance && BackgroundDynamicMaterialInstance)
		{
			FLinearColor BorderColor = CardsSettings->GetRarityColor(CardData->GetRarity());
			BorderDynamicMaterialInstance->SetVectorParameterValue(FName("Border Color"), BorderColor);

			FLinearColor BackgroundColor = CardsSettings->GetCategoryColor(CardData->GetCategory());
			BackgroundDynamicMaterialInstance->SetVectorParameterValue(FName("Background Color"), BackgroundColor);
		}
	}
}

void ACard::SetPlayerSubsystem()
{
	PlayerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerSubsystem>();
}

void ACard::HighlightCard(bool Active)
{
	HighlightBorder(Active);

	UCardInfoWidget* InfoWidget = Cast<UCardInfoWidget>(InfoWidgetComponent->GetWidget());
	if (InfoWidget)
	{
		if (Active)
		{
			InfoWidget->OnSelected();
		}
		else
		{
			InfoWidget->OnUnselected();
		}
	}
}

void ACard::HighlightBorder(bool Active)
{
	BorderDynamicMaterialInstance->SetScalarParameterValue(TEXT("Emission Strength"), Active ? EmissionStrengthSelect : EmissionStrengthDefault);
}

bool ACard::CanInteractAim()
{
	UInteractionComponent* InteractionComponent = PlayerSubsystem->GetInteractionComponentBoard();
	if (!InteractionComponent->IsAiming())
	{
		return true;
	}

	ACard* AimStartCard = Cast<ACard>(InteractionComponent->GetAimStart());
	if (!AimStartCard)
	{
		return true;
	}

	if (AimStartCard == this)
	{
		return false;
	}

	UCardUseBase* UseObject = CardData->GetUseObject();
	if (!UseObject)
	{
		return false;
	}

	if (!UseObject->IsCardAccepted(AimStartCard->GetCardData()))
	{
		return false;
	}

	return true;
}

bool ACard::StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType)
{		
	CurrentInteractionType = InteractionType;
	InteractionStartTime = GetWorld()->GetTimeSeconds();

	if (InteractionType == EInteractionType::Primary)
	{
		// If aiming
		UInteractionComponent* InteractionComponent = PlayerSubsystem->GetInteractionComponentBoard();
		if (InteractionComponent->IsAiming())
		{
			UCardUseBase* UseObject = CardData->GetUseObject();
			if (UseObject)
			{
				UseObject->Use(Cast<ACardBase>(InteractionComponent->GetAimStart()), this);
				InteractionComponent->DestroyInteractionAim();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Can't use - No use object!"))
			}

			return false;
		}

		//If not aiming
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
	if (CurrentInteractionType == EInteractionType::Primary)
	{
		// Refresh dummy 
		ACardManager* CardManager = PlayerSubsystem->GetCardManager();
		CardDummy = CardManager->EnableCardDummy();

		const FHitResult& HitResult = GetPlayerSubsystem()->GetHitResultUnderCursor();

		UPlayZoneComponent* HitPlayZone = GetPlayerSubsystem()->GetPlayZoneFromLocation(FVector2D(HitResult.Location));
		if (HitPlayZone)
		{
			int32 NewIndex = HitPlayZone->GetCardIndexFromLocation(HitResult.Location);
			if (UPlayZoneComponent* DummyZone = CardDummy->GetPlayZone())
			{
				if (DummyZone != HitPlayZone)
				{
					HitPlayZone->AddCard(CardDummy, NewIndex);
				}
				else
				{
					DummyZone->MoveCardToIndex(CardDummy, NewIndex);
				}
			}
			else
			{
				HitPlayZone->AddCard(CardDummy, NewIndex);
			}
		}
	}
	else if (CurrentInteractionType == EInteractionType::Secondary)
	{		
		float Delta = GetWorld()->GetDeltaSeconds();
		Progress += (Delta * 5.0f);

		FVector CurrentBarScale = ProgressBarMeshComponent->GetComponentScale();
		ProgressBarMeshComponent->SetWorldScale3D(FVector(CurrentBarScale.X, Progress, CurrentBarScale.Z));

		return Progress >= ProgressMax;
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
	if (!IsValid(this))
	{
		return false;
	}

	if (CurrentInteractionType == EInteractionType::Primary)
	{
		HighlightCard(false);
		SetActorEnableCollision(true);

		FVector CurrentLocation = GetActorLocation();

		// Add this Card to the PlayZone if available
		const FHitResult& HitResult = GetPlayerSubsystem()->GetHitResultUnderCursor();
		UPlayZoneComponent* HitPlayZone = GetPlayerSubsystem()->GetPlayZoneFromLocation(FVector2D(HitResult.Location));

		if (HitPlayZone)
		{
			int32 NewIndex = HitPlayZone->GetCardIndexFromLocation(HitResult.Location);
			HitPlayZone->AddCard(this, NewIndex);
		}
		else
		{
			if (UPlayZoneComponent* DummyPlayZone = CardDummy->GetPlayZone())
			{
				// Add the card in place of the dummy card
				DummyPlayZone->AddCard(this, DummyPlayZone->GetCardIndex(CardDummy));
			}
			else
			{
				FollowComponent->SetFollow(nullptr, FVector(CurrentLocation.X, CurrentLocation.Y, 0), FRotator());
			}
		}

		// Sometimes EndSelect is not called. Removing additional offset to fix it
		FollowComponent->RemoveAdditionalOffset();
	}
	else if (CurrentInteractionType == EInteractionType::Secondary)
	{
		ProgressBarMeshComponent->SetVisibility(false);
		Progress = 0.0f;

		float TimeSinceInteractionStart = GetWorld()->GetTimeSeconds() - InteractionStartTime;
		if (TimeSinceInteractionStart <= InteractionAimTimeThreshold)
		{
			UInteractionComponent* InteractionComponent = PlayerSubsystem->GetInteractionComponentBoard();
			InteractionComponent->GetInteractionAim(this);
		}
	}

	// Disable dummy
	if (CardDummy)
	{
		if (UPlayZoneComponent* Zone = CardDummy->GetPlayZone())
		{
			Zone->RemoveCard(CardDummy);
		}

		ACardManager* CardManager = PlayerSubsystem->GetCardManager();
		CardManager->DisableCardDummy();
		CardDummy = nullptr;
	}

	return true;
}

bool ACard::CanInteract_Implementation(EInteractionType InteractionType)
{
	return CanInteractAim();
}

bool ACard::StartSelect_Implementation(AActor* Interactor)
{
	bool PlayerInteracting = GetPlayerSubsystem()->IsPlayerInteracting();
	if (!PlayerInteracting)
	{
		// Transform
		FVector CurrentLocation = GetActorLocation();
		FollowComponent->SetAdditionalOffset(FVector(0, 0, 100));
		FollowComponent->SetFollowRotation(FRotator(25.0f, 0, 0));

		HighlightCard(true);
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
		// Transform
		FVector CurrentLocation = GetActorLocation();
		FollowComponent->RemoveAdditionalOffset();
		FollowComponent->SetFollowRotation(FRotator(0, 0, 0));

		HighlightCard(false);
	}

	return true;
}
