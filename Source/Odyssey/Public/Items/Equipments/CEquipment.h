#pragma once

#include "CoreMinimal.h"
#include "Items/CItem.h"
#include "Items/Equipments/Weapons/CWeaponStructures.h"
#include "CEquipment.generated.h"

class ACAttachment;

/**
 *	장착 가능한 모든 아이템의 부모 클래스
 *	3D 외형 정보와 장착/해제 관련 로직 소유
 */
UCLASS(Blueprintable)
class ODYSSEY_API UCEquipment : public UCItem
{
	GENERATED_BODY()
	
public:
	// 3D 외형을 담당할 Attachment 액터 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TSubclassOf<ACAttachment> AttachmentClass;

	// 월드에 실제로 스폰된 Attachment 액터의 인스턴스를 저장할 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<ACAttachment> Attachment;
	
	// 장착 애니메이션 등 데이터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FEquipmentData EquipmentData;

	// 장착/해제 관련 함수들 (나중에 WeaponComponent에서 호출)
	virtual void Equip();
	virtual void Unequip();
};
