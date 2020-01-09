// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tunnel.generated.h"

UCLASS()
class AVOID_API ATunnel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATunnel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class UStaticMeshComponent* Tunnel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class UStaticMeshComponent* WallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	class UBoxComponent* TriggerZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TArray<class UStaticMesh*> WallMeshs;

public:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	FVector GetSpawnPoint();

	void SetSpawner(class ATunnelSpawner* _TunnelSpawner);

	void RandomizeWall();

private:

	class ATunnelSpawner* TunnelSpawner;

	FTimerHandle TunnelDestroyTimerHandle;
	void TunnelDestory();

	float RotateSpeed;
};
