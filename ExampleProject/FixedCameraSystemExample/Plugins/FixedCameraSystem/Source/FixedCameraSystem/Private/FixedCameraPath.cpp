// Copyright 2023 German Lopez. All Rights Reserved.

#include "FixedCameraPath.h"

#pragma region UNREAL_ENGINE_EVENTS
/// <summary>
/// Sets default values for this actor's properties.
/// </summary>
AFixedCameraPath::AFixedCameraPath()
{
	// Disable Tick for Optimization
	PrimaryActorTick.bCanEverTick = false;

	// Camera Rail Configuration
	CameraPath = CreateDefaultSubobject<USplineComponent>("Camera Path");
	CameraPath->SetSelectedSplineSegmentColor(FColor::Green);
	CameraPath->SetUnselectedSplineSegmentColor(FColor::Green);
	CameraPath->SetTangentColor(FColor::Green);
	CameraPath->bVisualizeComponent = true;
	CameraPath->bShouldVisualizeScale = true;
	CameraPath->ScaleVisualizationWidth = 10;
	CameraPath->bAllowDiscontinuousSpline = false;

	// Setup Root Component
	RootComponent = CameraPath;
}

/// <summary>
/// Called when the game starts or when spawned.
/// </summary>
void AFixedCameraPath::BeginPlay()
{
	Super::BeginPlay();
}

/// <summary>
/// Called every frame
/// </summary>
/// <param name="DeltaTime">Time between frames.</param>
void AFixedCameraPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#pragma endregion

#pragma region CLASS_EVENTS
/// <summary>
/// Returns rail length.
/// </summary>
float AFixedCameraPath::GetRailLength()
{
	return CameraPath->GetSplineLength();
}

/// <summary>
/// Returns Location Along Rail.
/// </summary>
/// <param name="TravellingDistance">Travelling distance.</param>
/// <returns></returns>
FVector AFixedCameraPath::GetLocationAlongRail(float TravellingDistance)
{
	return CameraPath->GetLocationAtDistanceAlongSpline(TravellingDistance, ESplineCoordinateSpace::World);
}

/// <summary>
/// Returns first spline point location.
/// </summary>
FVector AFixedCameraPath::GetInitialLocation()
{
	return CameraPath->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
}
#pragma endregion