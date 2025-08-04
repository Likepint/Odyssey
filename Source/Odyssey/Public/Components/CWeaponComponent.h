#pragma once

#include "CoreMinimal.h"
#include "Components/CComponentBase.h"
#include "GameplayAbilitySpec.h"
#include "CWeaponComponent.generated.h"

class UEnhancedInputComponent;
class UInputAction;
class UCWeaponAsset;
class ACAttachment;
class UCWeapon;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword,
	Max UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponTypeChanged, EWeaponType, InNewType);

UCLASS()
class ODYSSEY_API UCWeaponComponent : public UCComponentBase
{
	GENERATED_BODY()

public:
	// AnimInstance가 구독할 델리게이트
	UPROPERTY(BlueprintAssignable)
	FWeaponTypeChanged OnWeaponTypeChanged;
	
	UCWeaponComponent();
	
	void SetupPlayerInput(UEnhancedInputComponent* PlayerInputComponent);
	
	// 외부에서 호출할 무기 장착/해제 함수
	UFUNCTION(BlueprintCallable)
	void Equip(EWeaponType InType);
	
	UFUNCTION(BlueprintCallable)
	void Unequip();

	// AnimNotify에서 호출할 무기 보관 함수
	void HolsterWeapon();

	// 전투 상태로 진입하는 함수
	void EnterCombat();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Action;
	
	// 에디터에서 무기 데이터 애셋들을 할당할 배열
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	TMap<EWeaponType, TObjectPtr<UCWeaponAsset>> WeaponDataAssets;
	
	// 생성된 Attachment 액터들을 보관할 TMap
	// Key: 무기 타입, Value: 스폰된 Attachment 액터 포인터
	UPROPERTY()
	TMap<EWeaponType, TObjectPtr<ACAttachment>> Attachments;
	
	// 현재 장착된 무기 타입
	UPROPERTY(VisibleAnywhere)
	EWeaponType CurrentWeaponType = EWeaponType::Max;

	// 현재 생성되어 캐릭터에 부착된 Attachment 액터
	UPROPERTY()
	TObjectPtr<UCWeapon> CurrentWeapon;
	
	// 현재 장착된 무기의 주 공격 어빌리티 핸들
	FGameplayAbilitySpecHandle ActionAbilityHandle;

	// 에디터에서 전투 해제 시간을 조절할 수 있도록 변수 추가
	UPROPERTY(EditAnywhere, Category = "Combat")
	float TimeToExitCombat = 7.0f; // 마지막 전투 행동 후 7초 뒤에 전투 상태 해제
	
	// 전투 상태 해제를 위한 타이머 핸들
	FTimerHandle ExitCombatTimerHandle; 

	// --- 전투 상태 관리 ---
	bool bIsInCombat = false;
	
	// 무기 타입을 변경하고 델리게이트를 방송하는 함수
	void ChangeWeaponType(EWeaponType InNewType);
	
	// 공격 입력이 들어왔을 때 호출될 함수
	void OnAction();
	
	// 타이머에 의해 호출되어 전투 상태를 해제하는 함수
	void ExitCombat();
};
