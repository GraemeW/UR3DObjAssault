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

	UE_LOG(LogTemp, Display, TEXT("BeginPlay:  %s"), *GetName());
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	MovePlatform(CurrentLocation, DeltaTime);
	UpdateDistanceMoved(CurrentLocation);
	FlipPlatformDirection();
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(FVector& CurrentLocation, float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("%s is moving..."), *GetName());
	CurrentLocation = CurrentLocation + GetPositionShift(DeltaTime);
	SetActorLocation(CurrentLocation);
}

void AMovingPlatform::FlipPlatformDirection()
{
	if (ShouldPlatformReturn())
	{
		MoveForward = !MoveForward;
		float DistanceRemaining = DistanceMoved - TurnAroundDistance / 2;

		UE_LOG(LogTemp, Display, TEXT("%s overshot the move distance by %f, compensating"), *GetName(), DistanceRemaining);

		DistanceMoved = -TurnAroundDistance / 2 - DistanceRemaining;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("%s is rotating..."), *GetName());
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

void AMovingPlatform::UpdateDistanceMoved(FVector CurrentLocation)
{
	DistanceMoved += FVector::Distance(CurrentLocation, LastLocation);
	LastLocation = CurrentLocation;
}

FVector AMovingPlatform::GetPositionShift(float DeltaTime) const
{
	return MoveForward ? PlatformSpeed * DeltaTime : PlatformSpeed * DeltaTime * -1;
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return (DistanceMoved > TurnAroundDistance / 2);
}

