// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AvoidGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AVOID_API AAvoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AAvoidGameModeBase();

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure, Category = "UMG")
	int32 GetCount();
	
	void AddCount(int32 Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	class USoundCue* BackgroundMusicSoundCue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;

	void GameOver();

private:

	int32 Count = 0;
};
