#include "Characters/CAnimInstanceBase.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"

void UCAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacterBase>(TryGetPawnOwner());
}

void UCAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	bIsCrouched = OwnerCharacter->bIsCrouched;
}
