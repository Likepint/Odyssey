#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "EnhancedInputComponent.h"
#include "Characters/CCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Items/Equipments/Weapons/CWeapon.h"
#include "Items/Equipments/Weapons/CWeaponAsset.h"
#include "Items/Equipments/CAttachment.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystems/Abilities/CGA_Action_MeleeAttack.h"

UCWeaponComponent::UCWeaponComponent()
{
}

void UCWeaponComponent::SetupPlayerInput(UEnhancedInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	
	if (IA_Action)
		PlayerInputComponent->BindAction(IA_Action, ETriggerEvent::Started, this, &UCWeaponComponent::OnAction);
}

void UCWeaponComponent::Equip(EWeaponType InType)
{
	// 이미 같은 무기를 장착하고 있다면 아무것도 하지 않음
	CheckTrue(CurrentWeaponType == InType);
	
	CheckNull(OwnerCharacter);
	
	UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	CheckNull(asc);

	// 장착할 무기의 데이터 애셋과 미리 생성된 Attachment 검색
	TObjectPtr<UCWeaponAsset>* assetPtr = WeaponDataAssets.Find(InType);
	TObjectPtr<ACAttachment>* attachmentPtr = Attachments.Find(InType);

	if (!assetPtr or !(*assetPtr) or !(*assetPtr)->WeaponClass or !attachmentPtr)
		return;
    
	Unequip(); // 장착 중인 무기 해제

	ChangeWeaponType(InType);
	
	UCWeaponAsset* weaponAsset = *assetPtr;
	ACAttachment* attachment = *attachmentPtr;
    
	// CWeapon 객체 생성
	CurrentWeapon = NewObject<UCWeapon>(this, weaponAsset->WeaponClass);
	CurrentWeapon->Attachment = attachment; // 미리 스폰된 Attachment 연결

	// '장착 소켓'으로 장착
	if (attachment)
		attachment->AttachToSocket(OwnerCharacter->GetMesh(), CurrentWeapon->EquipmentData.EquipSocketName);

	// Gameplay Ability 부여
	if (CurrentWeapon->ActionAbility)
		ActionAbilityHandle = asc->GiveAbility(FGameplayAbilitySpec(CurrentWeapon->ActionAbility, 1, 0, this));
}

void UCWeaponComponent::Unequip()
{
	if (CurrentWeaponType == EWeaponType::Max or !CurrentWeapon) return;

	// 장착 해제 몽타주가 있다면 재생
	if (CurrentWeapon->EquipmentData.UnequipMontage)
	{
		OwnerCharacter->PlayAnimMontage(CurrentWeapon->EquipmentData.UnequipMontage);
	}
	else // 몽타주가 없다면 즉시 무기 보관
	{
		HolsterWeapon();
	}
}

void UCWeaponComponent::HolsterWeapon()
{
	UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (asc and ActionAbilityHandle.IsValid())
	{
		asc->ClearAbility(ActionAbilityHandle);
		ActionAbilityHandle = FGameplayAbilitySpecHandle();
	}
    
	if (CurrentWeapon->Attachment)
		CurrentWeapon->Attachment->AttachToSocket(OwnerCharacter->GetMesh(), CurrentWeapon->EquipmentData.HolsterSocketName);
    
	CurrentWeapon = nullptr;
    ChangeWeaponType(EWeaponType::Max);
}

void UCWeaponComponent::EnterCombat()
{
	// 전투 상태에 진입하면, 정해진 시간 뒤에 ExitCombat을 호출하도록 타이머를 설정(또는 재설정)
	GetWorld()->GetTimerManager().SetTimer(ExitCombatTimerHandle, this, &UCWeaponComponent::ExitCombat, TimeToExitCombat, false);

	// 아직 전투 상태가 아니었다면, 상태를 변경하고 무기 장착
	if (bIsInCombat == false)
	{
		bIsInCombat = true;
		
		// Unarmed 상태가 아닐 때를 대비해 현재 무기를 다시 장착
		Equip(CurrentWeaponType == EWeaponType::Max ? EWeaponType::Sword : CurrentWeaponType);
	}
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// WeaponDataAssets에 등록된 모든 무기를 미리 생성하여 보관 소켓에 부착
	for (const TPair<EWeaponType, TObjectPtr<UCWeaponAsset>>& Pair : WeaponDataAssets)
	{
		if (Pair.Key == EWeaponType::Max)
			continue;

		if (!Pair.Value)
			continue;

		if ( !Pair.Value->WeaponClass)
			continue;

		UCWeapon* weaponData = Pair.Value->WeaponClass->GetDefaultObject<UCWeapon>();
		CheckNull(weaponData);
		CheckNull(weaponData->AttachmentClass);
		
		// Attachment 스폰
		ACAttachment* attachment = GetWorld()->SpawnActor<ACAttachment>(weaponData->AttachmentClass);
            
		// '보관 소켓'에 부착
		attachment->AttachToSocket(OwnerCharacter->GetMesh(), weaponData->EquipmentData.HolsterSocketName);
            
		// 맵에 저장
		Attachments.Add(Pair.Key, attachment);
	}
}

void UCWeaponComponent::ChangeWeaponType(EWeaponType InNewType)
{
	// 현재 타입과 같다면 리턴
	CheckTrue(CurrentWeaponType == InNewType);

	CurrentWeaponType = InNewType;

	// 델리게이트가 바인딩되어 있다면, 브로드캐스트
	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(CurrentWeaponType);
}

// 전투 상태 진입과 어빌리티 실행 '요청'만 담당
void UCWeaponComponent::OnAction()
{
	// 공격 시 항상 전투 상태에 돌입하고 타이머 갱신
	EnterCombat();
	
	// 현재 무기를 장착하지 않은 상태인지 확인
	if (CurrentWeaponType == EWeaponType::Max)
	{
		// 기본 무기(예: Sword) 장착
		Equip(EWeaponType::Sword);
	}

	UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	CheckNull(asc);
	
	// 현재 활성화된 어빌리티 중에 MeleeAttack이 있는지 확인
	for (const FGameplayAbilitySpec& spec : asc->GetActivatableAbilities())
	{
		if (spec.IsActive())
		{
			// 활성화된 어빌리티가 콤보가 가능한 MeleeAttack 어빌리티인지 확인
			if (UCGA_Action_MeleeAttack* ability = Cast<UCGA_Action_MeleeAttack>(spec.GetPrimaryInstance()))
			{
				// 만약 콤보가 진행 중이라면, 다음 콤보 시도
				ability->TryUpdateCombo();
				
				return;
			}
		}
	}
	
	// 진행 중인 콤보가 없다면, 새로운 공격 시작
	if (ActionAbilityHandle.IsValid())
		asc->TryActivateAbility(ActionAbilityHandle);
}

void UCWeaponComponent::ExitCombat()
{
	CheckFalse(bIsInCombat);

	bIsInCombat = false;
	
	Unequip();
	
	GetWorld()->GetTimerManager().ClearTimer(ExitCombatTimerHandle);
}
