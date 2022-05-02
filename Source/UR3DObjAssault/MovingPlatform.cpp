// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(InitialLocation);
	LastLocation = InitialLocation;
	DistanceMoved = 0;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = FVector(GetActorLocation());
	CurrentLocation.Y = CurrentLocation.Y + GetVelocity(DeltaTime);
	SetActorLocation(CurrentLocation);

	UpdateDistanceMoved(CurrentLocation);
}

float AMovingPlatform::GetVelocity(float DeltaTime)
{
	float Velocity = PlatformSpeed * DeltaTime;
	if (!MoveForward) { Velocity *= -1; }
	return Velocity;
}

void AMovingPlatform::UpdateDistanceMoved(FVector CurrentLocation)
{
	DistanceMoved += (CurrentLocation - LastLocation).Length();
	if (DistanceMoved > TurnAroundDistance / 2)
	{
		MoveForward = !MoveForward;
		DistanceMoved = -TurnAroundDistance / 2;
	}
}

