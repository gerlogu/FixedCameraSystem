// Copyright 2023 German Lopez. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "FixedCameraActor.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/BillboardComponent.h"
#include "FixedCameraTrigger.generated.h"

UCLASS()
class FIXEDCAMERASYSTEM_API AFixedCameraTrigger : public AActor
{
	GENERATED_BODY()

private:
	/// <summary>
	/// Debug collider 1 (just for Editor).
	/// </summary>
	UStaticMeshComponent* DebugCollider1;

	/// <summary>
	/// Debug collider 2 (just for Editor).
	/// </summary>
	UStaticMeshComponent* DebugCollider2;

	/// <summary>
	/// Box collision trigger component 1.
	/// </summary>
	UBoxComponent* Trigger1;

	/// <summary>
	/// Box collision trigger component 2.
	/// </summary>
	UBoxComponent* Trigger2;
	
public:	
	/// <summary>
	/// Root scene component.
	/// </summary>
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* Root;

	/// <summary>
	/// Fixed camera actor reference 2. (Names are swapped in C++ to simplify the code).
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Camera 1 (Orange Trigger)", Tooltip = "Fixed camera actor reference 1."))
	class AFixedCameraActor* Camera2;

	/// <summary>
	/// Smoothness transition quantity 2.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Smooth Transition (Camera 1)", EditCondition = "Camera2 != nullptr", EditConditionHides, ClampMin=0.f, Tooltip = "Smoothness transition quantity 1."))
	float fSmoothTransition2;

	/// <summary>
	/// Smoothness blend type 2.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Blend Type (Camera 1)", EditCondition = "Camera2 != nullptr && fSmoothTransition2 != 0", EditConditionHides, ClampMin = 0.f, Tooltip = "Smoothness blend type 1."))
	TEnumAsByte<EViewTargetBlendFunction> BlendFunc2;

	/// <summary>
	/// Smoothness blend exponent 2.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Blend Exponent (Camera 1)", EditCondition = "Camera2 != nullptr && fSmoothTransition2 != 0", EditConditionHides, ClampMin = 0.f, Tooltip = "Smoothness blend exponent 1."))
	float fBlendExp2;

	/// <summary>
	/// Fixed camera actor reference 1.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Camera 2 (Blue Trigger)", Tooltip = "Fixed camera actor reference 2."))
	class AFixedCameraActor* Camera1;

	/// <summary>
	/// Smoothness transition quantity 1.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Smooth Transition (Camera 2)", EditCondition = "Camera1 != nullptr", EditConditionHides, ClampMin = 0.f, Tooltip = "Smoothness transition quantity 2."))
	float fSmoothTransition1;

	/// <summary>
	/// Smoothness blend type 1.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Blend Type (Camera 2)", EditCondition = "Camera1 != nullptr && fSmoothTransition1 != 0", EditConditionHides, Tooltip = "Smoothness blend type 2."))
	TEnumAsByte<EViewTargetBlendFunction> BlendFunc1;

	/// <summary>
	/// Smoothness blend exponent 1.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Fixed Camera Trigger Settings", DisplayName = "Blend Exponent (Camera 2)", EditCondition = "Camera1 != nullptr && fSmoothTransition1 != 0", EditConditionHides, ClampMin = 0.f, Tooltip = "Smoothness blend exponent 2."))
	float fBlendExp1;

public:
	/// <summary>
	/// Sets default values for this actor's properties.
	/// </summary>
	AFixedCameraTrigger();

private:
	/// <summary>
	/// Overlap event - Trigger 1.
	/// </summary>
	/// <param name="OverlappedComp"></param>
	/// <param name="OtherActor"></param>
	/// <param name="OtherComp"></param>
	/// <param name="OtherBodyIndex"></param>
	/// <param name="bFromSweep"></param>
	/// <param name="SweepResult"></param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,  meta = (Tooltip="Overlap event - Trigger 1."))
	void OnBoxBeginOverlap1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/// <summary>
	/// Overlap event - Trigger 2.
	/// </summary>
	/// <param name="OverlappedComp"></param>
	/// <param name="OtherActor"></param>
	/// <param name="OtherComp"></param>
	/// <param name="OtherBodyIndex"></param>
	/// <param name="bFromSweep"></param>
	/// <param name="SweepResult"></param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (Tooltip = "Overlap event - Trigger 2."))
	void OnBoxBeginOverlap2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/// <summary>
	/// End overlap event - Trigger 1.
	/// </summary>
	/// <param name="OverlappedComp"></param>
	/// <param name="OtherActor"></param>
	/// <param name="OtherComp"></param>
	/// <param name="OtherBodyIndex"></param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (Tooltip = "End overlap event - Trigger 1."))
	void OnComponentEndOverlap1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/// <summary>
	/// End overlap event - Trigger 2.
	/// </summary>
	/// <param name="OverlappedComp"></param>
	/// <param name="OtherActor"></param>
	/// <param name="OtherComp"></param>
	/// <param name="OtherBodyIndex"></param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (Tooltip = "End overlap event - Trigger 2."))
	void OnComponentEndOverlap2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	/// <summary>
	/// Called when the game starts or when spawned.
	/// </summary>
	virtual void BeginPlay() override;

	/// <summary>
	/// Called in Editor.
	/// </summary>
	/// <param name="Transform"></param>
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	/// <summary>
	/// Called every frame.
	/// </summary>
	/// <param name="DeltaTime"></param>
	virtual void Tick(float DeltaTime) override;
};
