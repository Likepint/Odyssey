#include "Notifies/CAnimNotifyState_Combo.h"

#include "AbilitySystemComponent.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystems/Abilities/CGA_Action_MeleeAttack.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin
(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	float TotalDuration,
	const FAnimNotifyEventReference& EventReference
)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UAbilitySystemComponent* asc = CHelpers::GetComponent<UAbilitySystemComponent>(MeshComp->GetOwner());
	CheckNull(asc);

	// 현재 활성화된 어빌리티 중 MeleeAttack을 찾아 플래그를 true로 설정
	for (const FGameplayAbilitySpec& spec : asc->GetActivatableAbilities())
	{
		if (spec.IsActive())
		{
			if(UCGA_Action_MeleeAttack* ability = Cast<UCGA_Action_MeleeAttack>(spec.GetPrimaryInstance()))
			{
				ability->SetCanAcceptNextCombo(true);
				
				return;
			}
		}
	}
}

void UCAnimNotifyState_Combo::NotifyEnd
(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference
)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UAbilitySystemComponent* asc = CHelpers::GetComponent<UAbilitySystemComponent>(MeshComp->GetOwner());
	CheckNull(asc);

	// 현재 활성화된 어빌리티 중 MeleeAttack을 찾아 플래그를 false로 설정
	for (const FGameplayAbilitySpec& spec : asc->GetActivatableAbilities())
	{
		if (spec.IsActive())
		{
			if(UCGA_Action_MeleeAttack* ability = Cast<UCGA_Action_MeleeAttack>(spec.GetPrimaryInstance()))
			{
				ability->SetCanAcceptNextCombo(false);
				
				return;
			}
		}
	}
}
