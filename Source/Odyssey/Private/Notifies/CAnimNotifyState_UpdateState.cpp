#include "Notifies/CAnimNotifyState_UpdateState.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"
#include "Components/CMovementComponent.h"

FString UCAnimNotifyState_UpdateState::GetNotifyName_Implementation() const
{
	return "UpdateState";
}

void UCAnimNotifyState_UpdateState::NotifyTick
(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference
)
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
