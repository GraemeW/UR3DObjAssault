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

private:
	void MovePlatform(FVector& CurrentLocation, float DeltaTime);
	void UpdateDistanceMoved(FVector CurrentLocation);
	void FlipPlatformDirection();
	void RotatePlatform(float DeltaTime);

	FVector GetPositionShift(float DeltaTime) const;
	bool ShouldPlatformReturn() const;

	UPROPERTY(EditAnywhere, Category="Moving")
	FVector PlatformSpeed = FVector(0, 1000, 0);

	UPROPERTY(EditAnywhere, Category = "Moving")
	float TurnAroundDistance = 3000;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator RotationVelocity;

	UPROPERTY(VisibleAnywhere, Category = "Moving State")
	FVector InitialLocation = FVector(1.0, 2.0, 3.0);

	UPROPERTY(VisibleAnywhere, Category = "Moving State")
	bool MoveForward = true;

	UPROPERTY(VisibleAnywhere, Category = "Moving State")
	float DistanceMoved = 0;

	UPROPERTY(VisibleAnywhere, Category = "Moving State")
	FVector LastLocation = FVector(0, 0, 0);
};
