#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "PistolWeapon.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API APistolWeapon : public ABaseWeapon {
	GENERATED_BODY()
	
	public:
		APistolWeapon();
};
