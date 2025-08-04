#include "Characters/CAnimInstanceBase.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"
#include "Components/CWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacterBase>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
	
	if (UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter))
	{
		// WeaponComponent의 델리게이트에 OnWeaponTypeChanged 함수를 구독(바인딩)
		weaponComponent->OnWeaponTypeChanged.AddDynamic(this, &UCAnimInstanceBase::OnWeaponTypeChanged);
	}
}

void UCAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size();

	Acceleration = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Length();
	
	bIsCrouched = OwnerCharacter->bIsCrouched;
}

void UCAnimInstanceBase::OnWeaponTypeChanged(EWeaponType InNewType)
{
	// 애님 그래프에서 사용할 변수 업데이트
	WeaponType = InNewType;
}
