// CameraMovementType.h

#pragma once

#include "CoreMinimal.h"
//#include "CameraMovementType.generated.h"

UENUM(BlueprintType)
enum class ECameraMovementType : uint8
{
    CameraPan       UMETA(DisplayName = "Camera Pan"),
    CameraKeyboard  UMETA(DisplayName = "Camera Keyboard")
};
