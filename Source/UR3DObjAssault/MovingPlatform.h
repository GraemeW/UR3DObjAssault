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
	void UpdateDistanceMoved(FVector CurrentLocation);
	FVector GetPositionShift(float DeltaTime);

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	FVector PlatformSpeed = FVector(0, 1000, 0);

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float TurnAroundDistance = 3000;

	UPROPERTY(VisibleAnywhere, Category = "Moving Platform")
	FVector InitialLocation = FVector(1.0, 2.0, 3.0);

	UPROPERTY(VisibleAnywhere, Category = "Moving Platform")
	bool MoveForward = true;

	UPROPERTY(VisibleAnywhere, Category = "Moving Platform")
	float DistanceMoved = 0;

	UPROPERTY(VisibleAnywhere, Category = "Moving Platform")
	FVector LastLocation = FVector(0, 0, 0);
};
