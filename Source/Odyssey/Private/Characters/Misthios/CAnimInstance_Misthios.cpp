#include "Characters/Misthios/CAnimInstance_Misthios.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"
#include "Components/CMovementComponent.h"

void UCAnimInstance_Misthios::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCAnimInstance_Misthios::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	if (UCMovementComponent* movement = OwnerCharacter->FindComponentByClass<UCMovementComponent>())
	{
		bWantsToStop = movement->WantsToStop();
		if (bWantsToStop)
			SpeedAtStop = movement->GetSpeedAtStop();
	}
}
