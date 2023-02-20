// Copyright 2023 German Lopez. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Templates/SubclassOf.h"
#include "Styling/SlateStyle.h"

class FFixedCameraSystemModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedPtr<FSlateStyleSet> StyleSet;
};