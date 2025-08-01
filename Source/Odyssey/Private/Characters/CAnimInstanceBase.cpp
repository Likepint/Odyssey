#include "Characters/CAnimInstanceBase.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacterBase>(TryGetPawnOwner());
}

void UCAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size();

	Acceleration = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Length();
	
	bIsCrouched = OwnerCharacter->bIsCrouched;
}
