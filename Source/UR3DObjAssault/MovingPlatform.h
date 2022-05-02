// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class UR3DOBJASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateDistanceMoved(FVector CurrentLocation);

	float GetVelocity(float DeltaTime);

	UPROPERTY(EditAnywhere)
	FVector InitialLocation = FVector(1.0, 2.0, 3.0);

	UPROPERTY(EditAnywhere)
	float PlatformSpeed = 1;

	UPROPERTY(EditAnywhere)
	bool MoveForward = true;

	UPROPERTY(EditAnywhere)
	float TurnAroundDistance = 100;

	UPROPERTY(VisibleAnywhere)
	float DistanceMoved = 0;

	UPROPERTY(VisibleAnywhere)
	FVector LastLocation = FVector(0, 0, 0);
};
