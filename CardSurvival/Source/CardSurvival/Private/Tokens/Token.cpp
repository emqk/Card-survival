// Fill out your copyright notice in the Description page of Project Settings.


#include "Tokens/Token.h"
#include "Tokens/TokenData.h"
#include "Tokens/TokenInfoWidget.h"
#include "Tokens/TokenAmountWidget.h"
#include "Tokens/TokenStack.h"
#include "Utils/FollowComponent.h"
#include "Components/WidgetComponent.h"

AToken::AToken()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	TokenMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TokenMesh"));
	SetRootComponent(TokenMeshComponent);

	TextBackgroundComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TokenBackgroundMesh"));
	TextBackgroundComponent->SetupAttachment(TokenMeshComponent);
	TextBackgroundComponent->SetCollisionProfileName("NoCollision");

	InfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidgetComponent->SetCollisionProfileName("NoCollision");
	InfoWidgetComponent->SetupAttachment(TextBackgroundComponent);

	AmountWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("AmountWidget"));
	AmountWidgetComponent->SetCollisionProfileName("NoCollision");
	AmountWidgetComponent->SetupAttachment(TextBackgroundComponent);

	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}

bool AToken::StartSelect_Implementation(AActor* Interactor)
{
	if (!MyTokenStack->IsTokenOnTop(this))
	{
		return false;
	}

	FollowComponent->SetFollow(nullptr, FVector(DefaultWorldLocation.X, DefaultWorldLocation.Y, DefaultWorldLocation.Z + 50), FRotator(25, 0, 0));

	// Refresh the amount widget
	UTokenAmountWidget* TokenAmountWidget = Cast<UTokenAmountWidget>(AmountWidgetComponent->GetWidget());
	if (TokenAmountWidget)
	{
		TokenAmountWidget->Refresh(MyTokenStack->Tokens.Num());
	}

	// Show token info
	SetInfoActive(true);

	return true;
}

bool AToken::EndSelect_Implementation(AActor* Interactor)
{
	FollowComponent->SetFollow(nullptr, DefaultWorldLocation, FRotator(0, 0, 0));
	SetInfoActive(false);

	return false;
}

void AToken::ApplyData(UTokenData* Data)
{
	// Mesh
	TokenMeshComponent->SetStaticMesh(Data->GetMesh());

	// Widget
	UTokenInfoWidget* TokenInfoWidget = Cast<UTokenInfoWidget>(InfoWidgetComponent->GetWidget());
	if (TokenInfoWidget)
	{
		TokenInfoWidget->Refresh(Data, 0);
	}
}

void AToken::SetInfoActive(bool Active)
{
	TextBackgroundComponent->SetVisibility(Active);
	InfoWidgetComponent->SetVisibility(Active);	
	AmountWidgetComponent->SetVisibility(Active);	

	bIsInfoActive = Active;
}
