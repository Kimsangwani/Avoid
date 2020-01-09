// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TunnelSpawner.generated.h"

UCLASS()
class AVOID_API ATunnelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATunnelSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<class ATunnel> TunnelClass;

private:

	void SpawnTunnel(FVector Location);

	class ATunnel* NewestTunnel;

public:

	void SpawnTunnelAtSpawnPoint();
	void SpawnInitialTunnels();

};
