#include "Notifies/CAnimNotifyState_StateUpdate.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"
#include "Components/CMovementComponent.h"

void UCAnimNotifyState_StateUpdate::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	if (ACCharacterBase* character = Cast<ACCharacterBase>(MeshComp->GetOwner()))
	{
		if (UCMovementComponent* movementComponent = CHelpers::GetComponent<UCMovementComponent>(character))
			movementComponent->CheckStopSpeed();
	}
}
