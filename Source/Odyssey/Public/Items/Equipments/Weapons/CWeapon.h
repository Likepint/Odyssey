#pragma once

#include "CoreMinimal.h"
#include "Items/Equipments/CEquipment.h"
#include "CWeapon.generated.h"

class UGameplayAbility;

/**
 *	공격 기능이 있는 모든 무기 아이템의 부모 클래스
 *	추가로 GAS 어빌리티 정보 소유
 */
UCLASS()
class ODYSSEY_API UCWeapon : public UCEquipment
{
	GENERATED_BODY()

public:
	// 이 무기를 장착했을 때 사용할 주 공격 어빌리티
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayAbility> ActionAbility;
};
