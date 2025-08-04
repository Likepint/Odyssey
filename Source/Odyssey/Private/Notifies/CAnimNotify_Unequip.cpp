#include "Notifies/CAnimNotify_Unequip.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"
#include "Components/CWeaponComponent.h"

FString UCAnimNotify_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip";
}

void UCAnimNotify_Unequip::Notify
(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference
)
{
	Super::Notify(MeshComp, Animation, EventReference);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	
	// 캐릭터를 가져옵니다.
	ACCharacterBase* character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(character);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(character);
	CheckNull(weapon);

	weapon->HolsterWeapon();
}
