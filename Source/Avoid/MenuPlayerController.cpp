// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AMenuPlayerController::AMenuPlayerController()
{

}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitWidget();
}

void AMenuPlayerController::Play(FName Level)
{
	UGameplayStatics::OpenLevel(this, Level, true);
}

void AMenuPlayerController::Exit()
{
	FGenericPlatformMisc::RequestExit(false);
}

void AMenuPlayerController::SetVisible()
{
	if (HowPlayingWidgetClass)
	{
		if (HowPlayingWidget->IsVisible())
		{
			HowPlayingWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			HowPlayingWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMenuPlayerController::InitWidget()
{
	if (MenuWidgetClass)
	{
		FInputModeUIOnly InputMode;
		this->SetInputMode(InputMode);
		this->bShowMouseCursor = true;

		MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}

	if (HowPlayingWidgetClass)
	{
		HowPlayingWidget = CreateWidget<UUserWidget>(GetWorld(), HowPlayingWidgetClass);
		HowPlayingWidget->SetDesiredSizeInViewport(FVector2D(700.0f, 500.0f));
		HowPlayingWidget->SetAnchorsInViewport(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
		HowPlayingWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
		HowPlayingWidget->SetVisibility(ESlateVisibility::Hidden);
		HowPlayingWidget->AddToViewport();
	}
}
