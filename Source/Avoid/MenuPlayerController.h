// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AVOID_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMenuPlayerController();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
		TSubclassOf<class UUserWidget> MenuWidgetClass;
	class UUserWidget* MenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
		TSubclassOf<class UUserWidget> HowPlayingWidgetClass;
	class UUserWidget* HowPlayingWidget;

public:

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void Play(FName Level);
	UFUNCTION(BlueprintCallable, Category = "UMG")
	void Exit();

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void SetVisible();

private:

	void InitWidget();
};
