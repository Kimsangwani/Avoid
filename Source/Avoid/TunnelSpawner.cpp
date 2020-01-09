// Fill out your copyright notice in the Description page of Project Settings.


#include "TunnelSpawner.h"
#include "Tunnel.h"
#include "Engine/World.h"
#include "Avoider.h"

// Sets default values
ATunnelSpawner::ATunnelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATunnelSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnInitialTunnels();
}

// Called every frame
void ATunnelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATunnelSpawner::SpawnTunnel(FVector Location)
{
	FRotator Rotator = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (TunnelClass)
	{
		NewestTunnel = GetWorld()->SpawnActor<ATunnel>(TunnelClass, Location, Rotator, SpawnParams);
		NewestTunnel->SetSpawner(this);
		NewestTunnel->RandomizeWall();
	}
}

void ATunnelSpawner::SpawnTunnelAtSpawnPoint()
{
	SpawnTunnel(NewestTunnel->GetSpawnPoint());
}

void ATunnelSpawner::SpawnInitialTunnels()
{
	for (int i = 0; i < 2; i++)
	{
		if (NewestTunnel)
		{
			SpawnTunnelAtSpawnPoint();
		}
		else
		{
			AAvoider* Avoider = Cast<AAvoider>(GetWorld()->GetFirstPlayerController()->GetPawn());
			SpawnTunnel(Avoider->GetActorLocation());
		}
	}
}


