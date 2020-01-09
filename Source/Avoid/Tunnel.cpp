// Fill out your copyright notice in the Description page of Project Settings.


#include "Tunnel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "TunnelSpawner.h"
#include "Avoider.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Engine/StaticMesh.h"
#include "AvoidGameModeBase.h"

// Sets default values
ATunnel::ATunnel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Tunnel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tunnel"));

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->InitBoxExtent(FVector(32, 500, 500));
	TriggerZone->SetRelativeLocation(FVector(2532, 0, 0));

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->SetRelativeLocation(FVector(2500, 0, 0));

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	WallMesh->SetupAttachment(RootComponent);
	WallMesh->SetRelativeLocation(FVector(2470, 0, 0));
}

// Called when the game starts or when spawned
void ATunnel::BeginPlay()
{
	Super::BeginPlay();

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ATunnel::OnBeginOverlap);
	WallMesh->OnComponentHit.AddDynamic(this, &ATunnel::OnHit);
	Tunnel->OnComponentHit.AddDynamic(this, &ATunnel::OnHit);

	int Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
	{
		RotateSpeed = FMath::RandRange(20.0f, 50.0f);
	}
	else
	{
		RotateSpeed = FMath::RandRange(-20.0f, -50.0f);
	}
	
}

// Called every frame
void ATunnel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WallMesh->AddLocalRotation(FRotator(0.0f, 0.0f, RotateSpeed * DeltaTime));
}

void ATunnel::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAvoider* Avoider = Cast<AAvoider>(OtherActor);
	if (Avoider)
	{
		TunnelSpawner->SpawnTunnelAtSpawnPoint();
		GetWorld()->GetTimerManager().SetTimer(TunnelDestroyTimerHandle, this, &ATunnel::TunnelDestory, 1.f, false);

		AAvoidGameModeBase *AvoidGameModeBase = Cast<AAvoidGameModeBase>(GetWorld()->GetAuthGameMode());
		AvoidGameModeBase->AddCount(1);
		
		Avoider->IncreaseMoveSpeed();
	}

}

void ATunnel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AAvoider* Avoider = Cast<AAvoider>(OtherActor);
	if (Avoider)
	{
		Avoider->GameOver();
	}
}

FVector ATunnel::GetSpawnPoint()
{
	return SpawnPoint->GetComponentTransform().GetLocation();
}

void ATunnel::SetSpawner(ATunnelSpawner* _TunnelSpawner)
{
	TunnelSpawner = _TunnelSpawner;
}

void ATunnel::TunnelDestory()
{
	Destroy();
}

void ATunnel::RandomizeWall()
{
	int Index = FMath::RandRange(0, 3);
	float RandomRotation = FMath::RandRange(0, 360);
	FRotator Rotator = FRotator(0.0f, 0.0f, RandomRotation);

	WallMesh->SetStaticMesh(WallMeshs[Index]);
	WallMesh->AddLocalRotation(Rotator);
}

