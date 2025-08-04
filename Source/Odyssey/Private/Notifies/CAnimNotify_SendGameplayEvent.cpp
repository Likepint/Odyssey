#include "Notifies/CAnimNotify_SendGameplayEvent.h"
#include "Global.h"
#include "AbilitySystemBlueprintLibrary.h"

FString UCAnimNotify_SendGameplayEvent::GetNotifyName_Implementation() const
{
	return "SendGameplayEvent";
}

void UCAnimNotify_SendGameplayEvent::Notify
(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference
)
{
	Super::Notify(MeshComp, Animation, EventReference);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// FGameplayEventData를 만들고, 이 노티파이에 설정된 EventTag를 사용하여 이벤트 전송
	FGameplayEventData Payload;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, Payload);
}
