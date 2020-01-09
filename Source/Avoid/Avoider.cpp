// Fill out your copyright notice in the Description page of Project Settings.


#include "Avoider.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "AvoiderPlayerController.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "AvoidGameModeBase.h"

// Sets default values
AAvoider::AAvoider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Avoider = CreateDefaultSubobject<USphereComponent>(TEXT("Avoider"));
	Avoider->SetSphereRadius(16.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AAvoider::BeginPlay()
{
	Super::BeginPlay();
	
	ForwardSpeed = 1000.0f;
	IsDead = false;
}

// Called every frame
void AAvoider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead)
	{
		AddActorWorldOffset(FVector(ForwardSpeed * DeltaTime, 0.0f, 0.0f), true);
	}

	Move(DeltaTime);
}

// Called to bind functionality to input
void AAvoider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("UpDown", this, &AAvoider::MoveUpDown);
	PlayerInputComponent->BindAxis("RightLeft", this, &AAvoider::MoveRightLeft);
}

void AAvoider::MoveUpDown(float AxisValue)
{
	MovementInput.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 500.0f;
}

void AAvoider::MoveRightLeft(float AxisValue)
{
	MovementInput.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 500.0f;
}

void AAvoider::Move(float DeltaTime)
{
	if (!IsDead && !MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal() * 500.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * MovementInput.Z * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

void AAvoider::IncreaseMoveSpeed()
{
	ForwardSpeed = FMath::Clamp(ForwardSpeed * 1.05f, 1000.0f, 2000.0f);
}

void AAvoider::SetIsDead(bool _IsDead)
{
	IsDead = _IsDead;
}

void AAvoider::GameOver()
{
	IsDead = true;

	AAvoiderPlayerController* AvoiderPlayerController = Cast<AAvoiderPlayerController>(GetWorld()->GetFirstPlayerController());
	AvoiderPlayerController->GameOver();

	AAvoidGameModeBase* AvoidGameModeBase = Cast<AAvoidGameModeBase>(GetWorld()->GetAuthGameMode());
	AvoidGameModeBase->GameOver();
}

