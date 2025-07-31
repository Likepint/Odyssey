#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h" // UENUM 매크로를 위해 필요

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Alexios = 0,
	Kassandra,
	Max UMETA(Hidden)
};