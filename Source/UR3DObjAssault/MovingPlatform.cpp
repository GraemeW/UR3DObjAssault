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

	InitialLocation = GetActorLocation();
	LastLocation = InitialLocation;
	DistanceMoved = 0;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + GetPositionShift(DeltaTime);
	SetActorLocation(CurrentLocation);

	UpdateDistanceMoved(CurrentLocation);
}

FVector AMovingPlatform::GetPositionShift(float DeltaTime)
{
	return MoveForward ? PlatformSpeed * DeltaTime : PlatformSpeed * DeltaTime * -1;
}

void AMovingPlatform::UpdateDistanceMoved(FVector CurrentLocation)
{
	DistanceMoved += FVector::Distance(CurrentLocation, LastLocation);
	if (DistanceMoved > TurnAroundDistance / 2)
	{
		MoveForward = !MoveForward;
		float DistanceRemaining = DistanceMoved - TurnAroundDistance / 2;
		DistanceMoved = -TurnAroundDistance / 2 - DistanceRemaining;
	}
	LastLocation = CurrentLocation;
}

