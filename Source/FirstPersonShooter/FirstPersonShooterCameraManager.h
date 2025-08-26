#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "FirstPersonShooterCameraManager.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API AFirstPersonShooterCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	public:
		AFirstPersonShooterCameraManager();
};
