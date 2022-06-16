// Fill out your copyright notice in the Description page of Project Settings.


#include "Tokens/Token.h"
#include "Tokens/TokenData.h"
#include "Tokens/TokenInfoWidget.h"
#include "Utils/FollowComponent.h"
#include "Components/WidgetComponent.h"

AToken::AToken()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	TokenMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TokenMesh"));
	TokenMeshComponent->SetupAttachment(RootComponent);
	TextBackgroundComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TokenBackgroundMesh"));
	TextBackgroundComponent->SetupAttachment(TokenMeshComponent);
	InfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidgetComponent->SetupAttachment(TextBackgroundComponent);

	FollowComponent = CreateDefaultSubobject<UFollowComponent>(TEXT("FollowComponent"));
}

void AToken::ApplyData(UTokenData* Data)
{
	// Mesh
	TokenMeshComponent->SetStaticMesh(Data->GetMesh());

	// Widget
	UTokenInfoWidget* TokenInfoWidget = Cast<UTokenInfoWidget>(InfoWidgetComponent->GetWidget());
	if (TokenInfoWidget)
	{
		TokenInfoWidget->Refresh(Data->GetName(), Data->GetDescription());
	}
}

void AToken::SetInfoActive(bool Active)
{
	TextBackgroundComponent->SetVisibility(Active);
	InfoWidgetComponent->SetVisibility(Active);	

	bIsInfoActive = Active;
}
