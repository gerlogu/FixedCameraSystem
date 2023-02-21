// Copyright 2023 German Lopez. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "FixedCameraPath.generated.h"

UCLASS()
class FIXEDCAMERASYSTEM_API AFixedCameraPath : public AActor
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Camera Rail Path.
	/// </summary>
	UPROPERTY(VisibleAnywhere, meta = (Category = "Fixed Camera Path", Tooltip = "Camera Rail Path."))
	USplineComponent* CameraPath;

public:	
	/// <summary>
	/// Sets default values for this actor's properties.
	/// </summary>
	AFixedCameraPath();

	/// <summary>
	/// Returns rail length.
	/// </summary>
	UFUNCTION(BlueprintCallable, meta = (Category = "Fixed Camera Path", Tooltip = "Returns rail length."))
	float GetRailLength();

	/// <summary>
	/// Returns first spline point location.
	/// </summary>
	UFUNCTION(BlueprintCallable, meta = (Category = "Fixed Camera Path", Tooltip = "Returns first spline point location."))
	FVector GetInitialLocation();


	/// <summary>
	/// Returns Location Along Rail.
	/// </summary>
	/// <param name="TravellingDistance">Travelling distance.</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, meta = (Category = "Fixed Camera Path", Tooltip = "Returns Location Along Rail."))
	FVector GetLocationAlongRail(float TravellingDistance);

	/// <summary>
	/// Called every frame
	/// </summary>
	/// <param name="DeltaTime">Time between frames.</param>
	virtual void Tick(float DeltaTime) override;

protected:
	/// <summary>
	/// Called when the game starts or when spawned.
	/// </summary>
	virtual void BeginPlay() override;
};
