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

	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay:  %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	MovePlatform(CurrentLocation, DeltaTime);
	UpdateDistanceMoved(CurrentLocation);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(FVector& CurrentLocation, float DeltaTime)
{
	CurrentLocation = CurrentLocation + GetPositionShift(DeltaTime);
	SetActorLocation(CurrentLocation);
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		MoveForward = !MoveForward;
		float DistanceRemaining = DistanceMoved - TurnAroundDistance / 2;

		FString Name = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s overshot the move distance by %f, compensating"), *Name, DistanceRemaining);

		DistanceMoved = -TurnAroundDistance / 2 - DistanceRemaining;
	}
}

FVector AMovingPlatform::GetPositionShift(float DeltaTime)
{
	return MoveForward ? PlatformSpeed * DeltaTime : PlatformSpeed * DeltaTime * -1;
}

void AMovingPlatform::UpdateDistanceMoved(FVector CurrentLocation)
{
	DistanceMoved += FVector::Distance(CurrentLocation, LastLocation);
	LastLocation = CurrentLocation;
}

bool AMovingPlatform::ShouldPlatformReturn()
{
	return (DistanceMoved > TurnAroundDistance / 2);
}

