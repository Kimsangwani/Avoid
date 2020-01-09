// Fill out your copyright notice in the Description page of Project Settings.


#include "AvoidGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

AAvoidGameModeBase::AAvoidGameModeBase()
{
	RootComponent = AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AAvoidGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (BackgroundMusicSoundCue->IsValidLowLevelFast()) 
	{
		AudioComponent->SetSound(BackgroundMusicSoundCue);
		AudioComponent->Play();
	}
}

int32 AAvoidGameModeBase::GetCount()
{
	return Count;
}

void AAvoidGameModeBase::AddCount(int32 Value)
{
	Count += Value;
}

void AAvoidGameModeBase::GameOver()
{
	AudioComponent->Stop();
}

