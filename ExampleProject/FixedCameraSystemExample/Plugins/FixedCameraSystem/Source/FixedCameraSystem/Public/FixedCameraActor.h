// Copyright 2023 German Lopez. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "FixedCameraPath.h"
#include "Camera/PlayerCameraManager.h"
#include "FixedCameraActor.generated.h"

UENUM()
enum class ECameraFocus
{
	NoFocus        UMETA(DisplayName = "No Focus"),
	FocusOnPlayer  UMETA(DisplayName = "Focus on Player"),
	FocusOnObject  UMETA(DisplayName = "Focus on Target"),
	MiddleLocationPlayerAndInitialFocus  UMETA(DisplayName = "Middle location (Player and Initial Focus)"),
	MiddleLocationPlayerAndObject		 UMETA(DisplayName = "Middle location (Player and Target)"),
};

UENUM()
enum class ECameraType
{
	Static  UMETA(DisplayName = "Static Camera"),
	Rail    UMETA(DisplayName = "On Rail Camera")
};


UCLASS()
class FIXEDCAMERASYSTEM_API AFixedCameraActor : public AActor
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Initializes this camera by default.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings", DisplayName = "Activate on Play", Tooltip = "Initializes this camera by default."))
	bool bDefaultCamera;
	
	/// <summary>
	/// Defines the type of camera: Static or On Rail.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings", InlineCategoryProperty, Tooltip = "Defines the type of camera: Static or On Rail."))
	ECameraType CameraType;

	/// <summary>
	/// Fixed Camera Rail actor reference.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings", EditCondition = "CameraType == ECameraType::Rail", EditConditionHides, Tooltip = "Fixed Camera Rail actor reference."))
	class AFixedCameraPath* CameraRail;

	/// <summary>
	/// Distance to reach the last point of the rail.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings", DisplayName = "Rail Travelling Distance", EditCondition = "CameraType == ECameraType::Rail", EditConditionHides, Tooltip = "Distance to reach the last point of the rail."))
	float fRailTravellingDistance = 2000.f;

	/// <summary>
	/// Determines if smooth movement will be used.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings", DisplayName = "Smooth Movement", EditCondition = "CameraType == ECameraType::Rail", EditConditionHides, Tooltip = "Determines if smooth movement will be used."))
	bool bSmoothMovement = true;

	/// <summary>
	/// Smoothness movement velocity.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings", DisplayName = "Smooth Movement Speed", EditCondition = "bSmoothMovement && CameraType == ECameraType::Rail", EditConditionHides, Tooltip = "Smoothness movement velocity.", ClampMin = "0.0"))
	float fSmoothMovementSpeed = 3.f;

	/// <summary>
	/// Camera focus type.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings|Focus Parameters", Tooltip = "Camera focus type."))
	ECameraFocus CameraFocus;

	/// <summary>
	/// Focus target actor reference.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings|Focus Parameters", EditCondition = "CameraFocus == ECameraFocus::FocusOnObject || CameraFocus == ECameraFocus::MiddleLocationPlayerAndObject", EditConditionHides, Tooltip = "Focus target actor reference."))
	class AActor* FocusTarget;

	/// <summary>
	/// Middle point alpha (0 to 1).
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings|Focus Parameters", EditCondition = "CameraFocus == ECameraFocus::MiddleLocationPlayerAndObject || CameraFocus == ECameraFocus::MiddleLocationPlayerAndInitialFocus", EditConditionHides, Tooltip = "Middle point alpha (0 to 1).", DisplayName = "Middle Point Alpha", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float fMiddlePointAlpha = 0.25f;

	/// <summary>
	/// Determines if smooth rotation will be used.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings|Focus Parameters", DisplayName = "Smooth Rotation", EditCondition = "CameraFocus != ECameraFocus::NoFocus", EditConditionHides, Tooltip = "Determines if smooth rotation will be used."))
	bool bSmoothRotation = true;

	/// <summary>
	/// Smoothness rotation velocity.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings|Focus Parameters", DisplayName = "Smooth Rotation Speed", EditCondition = "bSmoothRotation && CameraFocus != ECameraFocus::NoFocus", EditConditionHides, Tooltip = "Smoothness rotation velocity.", ClampMin = "0.0"))
	float fSmoothRotationSpeed = 3.f;

	/// <summary>
	/// Auto-Disables tick after deactivating the camera.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Settings|Optimization", DisplayName = "Auto-Deactivate Tick Method", Tooltip = "Auto-Disables tick after deactivating the camera."))
	bool bAutoDeactivateTickMethod;

	/// <summary>
	/// Camera component (Root).
	/// </summary>
	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* Camera;

private:
	/// <summary>
	/// First frame camera rotation.
	/// </summary>
	FRotator originalCameraRotation;

	/// <summary>
	/// Player character reference.
	/// </summary>
	AActor* PlayerCharacterActorReference;

public:	

	/// <summary>
	/// Sets default values for this actor's properties.
	/// </summary>
	AFixedCameraActor();

protected:
	/// <summary>
	/// Called on Editor.
	/// </summary>
	/// <param name="Transform">Actor transform.</param>
	virtual void OnConstruction(const FTransform& Transform) override;

	/// <summary>
	/// Called when the game starts or when spawned
	/// </summary>
	virtual void BeginPlay() override;

public:	
	/// <summary>
	/// Called every frame.
	/// </summary>
	/// <param name="DeltaTime">Time between frames.</param>
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Activates the camera actor.
	/// </summary>
	/// <param name="fSmoothTransition">Smoothness quantity.</param>
	/// <param name="BlendFunction">Smoothness type.</param>
	/// <param name="fBlendExponent">Smoothness blend exponent.</param>
	void ActivateFixedCamera(float fSmoothTransition, TEnumAsByte<EViewTargetBlendFunction> BlendFunction, float fBlendExponent);
	
	/// <summary>
	/// Deactivates the camera actor.
	/// </summary>
	void DeactivateFixedCamera();
};
