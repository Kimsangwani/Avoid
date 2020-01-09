// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AvoiderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AVOID_API AAvoiderPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AAvoiderPlayerController();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> GameOverWidgetClass;
	class UUserWidget* GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	class UUserWidget* HUDWidget;

public:

	void GameOver();
	
	UFUNCTION(BlueprintCallable, Category = "UMG")
	void Exit();
	UFUNCTION(BlueprintCallable, Category = "UMG")
	void ReStart(FName Level);

private:

	void InitWidget();
};
