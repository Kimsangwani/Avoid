// Fill out your copyright notice in the Description page of Project Settings.


#include "AvoiderPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Avoider.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AAvoiderPlayerController::AAvoiderPlayerController()
{

}

void AAvoiderPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitWidget();
}

void AAvoiderPlayerController::GameOver()
{
	if (GameOverWidgetClass)
	{
		FInputModeUIOnly InputMode;
		this->SetInputMode(InputMode);
		this->bShowMouseCursor = true;

		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
		}
	}
}

void AAvoiderPlayerController::Exit()
{
	FGenericPlatformMisc::RequestExit(false);
}

void AAvoiderPlayerController::ReStart(FName Level)
{
	UGameplayStatics::OpenLevel(this, Level, true);
}

void AAvoiderPlayerController::InitWidget()
{
	if (HUDWidgetClass)
	{
		FInputModeGameOnly InputMode;
		this->SetInputMode(InputMode);
		this->bShowMouseCursor = false;

		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
