#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/Equipments/Weapons/CWeaponStructures.h"
#include "CWeaponAsset.generated.h"

class UCWeapon;

/**
 * 무기 하나의 모든 정보를 담는 데이터 애셋
 * WeaponComponent가 어떤 종류의 무기를 생성하고 장착할지 결정하는 '설계도' 역할
 */
UCLASS()
class ODYSSEY_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// 설계도를 통해 생성할 무기 아이템의 클래스
	// 예를 들어, 'CWeapon_Sword' 클래스를 여기에 지정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UCWeapon> WeaponClass;
};
