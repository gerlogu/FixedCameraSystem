// Copyright 2023 German Lopez. All Rights Reserved.

#include "FixedCameraSystem.h"
#include "PlacementMode/Public/IPlacementModeModule.h"
#include "ActorFactories/ActorFactoryBlueprint.h"
#include "Interfaces/IPluginManager.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"

#define LOCTEXT_NAMESPACE "FixedCameraSystem"

/// <summary>
/// Executed during module initialization.
/// </summary>
void FFixedCameraSystemModule::StartupModule()
{
	int Priority = 41;
	FPlacementCategoryInfo FixedCameraSystem( LOCTEXT("FixedCamera", "Fixed Camera"), "FixedCamera", TEXT("FixedCamera"), Priority);
	IPlacementModeModule::Get().RegisterPlacementCategory(FixedCameraSystem);

	// Find and register actors to category
	UBlueprint* FixedCamera = Cast<UBlueprint>(FSoftObjectPath(TEXT("/FixedCameraSystem/Blueprints/FixedCamera.FixedCamera")).TryLoad());
	if (FixedCamera) 
	{
		IPlacementModeModule::Get().RegisterPlaceableItem(FixedCameraSystem.UniqueHandle, MakeShareable(new FPlaceableItem(
			*UActorFactory::StaticClass(),
			FAssetData(FixedCamera, true),
			FName("FixedCamera_Thumbnail"),
			#if ENGINE_MAJOR_VERSION == 5
				FName("FixedCamera_Icon"),
			#endif
			TOptional<FLinearColor>(),
			TOptional<int32>(),
			NSLOCTEXT("PlacementMode", "Fixed Camera", "Fixed Camera")
		)));
	}

	UBlueprint* FixedCameraPath = Cast<UBlueprint>(FSoftObjectPath(TEXT("/FixedCameraSystem/Blueprints/FixedCameraRail.FixedCameraRail")).TryLoad());
	if (FixedCameraPath) 
	{
		IPlacementModeModule::Get().RegisterPlaceableItem(FixedCameraSystem.UniqueHandle, MakeShareable(new FPlaceableItem(
			*UActorFactory::StaticClass(),
			FAssetData(FixedCameraPath, true),
			FName("Spline_Thumbnail"),
			#if ENGINE_MAJOR_VERSION == 5
				FName("Spline_Icon"),
			#endif
			TOptional<FLinearColor>(),
			TOptional<int32>(),
			NSLOCTEXT("PlacementMode", "Fixed Camera | Path", "Fixed Camera | Path")
		)));
	}

	UBlueprint* FixedCameraTrigger = Cast<UBlueprint>(FSoftObjectPath(TEXT("/FixedCameraSystem/Blueprints/FixedCameraTrigger.FixedCameraTrigger")).TryLoad());
	if (FixedCameraTrigger) 
	{
		IPlacementModeModule::Get().RegisterPlaceableItem(FixedCameraSystem.UniqueHandle, MakeShareable(new FPlaceableItem(
			*UActorFactory::StaticClass(),
			FAssetData(FixedCameraTrigger, true),
			FName("Trigger_Thumbnail"),
			#if ENGINE_MAJOR_VERSION == 5
				FName("Trigger_Icon"),
			#endif
			TOptional<FLinearColor>(),
			TOptional<int32>(),
			NSLOCTEXT("PlacementMode", "Fixed Camera | Trigger", "Fixed Camera | Trigger")
		)));
	}

	StyleSet = MakeShareable(new FSlateStyleSet("FixedCameraSystemStyle"));

	FString CameraIconPath = IPluginManager::Get().FindPlugin(TEXT("FixedCameraSystem"))->GetBaseDir() + TEXT("/Resources/");
	
	StyleSet->Set("FixedCamera_Thumbnail", new FSlateImageBrush(CameraIconPath + TEXT("FixedCamera_Thumbnail.png"), FVector2D(64.f, 64.f)));
	StyleSet->Set("Spline_Thumbnail", new FSlateImageBrush(CameraIconPath + TEXT("Spline_Thumbnail.png"), FVector2D(64.f, 64.f)));
	StyleSet->Set("Trigger_Thumbnail", new FSlateImageBrush(CameraIconPath + TEXT("Trigger_Thumbnail.png"), FVector2D(64.f, 64.f)));
	StyleSet->Set("Target_Thumbnail", new FSlateImageBrush(CameraIconPath + TEXT("Target_Thumbnail.png"), FVector2D(64.f, 64.f)));
		
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

/// <summary>
/// Executed during module shutdown.
/// </summary>
void FFixedCameraSystemModule::ShutdownModule()
{
	if (IPlacementModeModule::IsAvailable())
	{
		IPlacementModeModule::Get().UnregisterPlacementCategory("FixedCameraSystem");
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	StyleSet.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFixedCameraSystemModule, FixedCameraSystem)