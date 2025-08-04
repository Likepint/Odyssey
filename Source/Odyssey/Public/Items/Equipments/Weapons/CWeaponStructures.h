#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CWeaponStructures.generated.h"

class UAnimMontage;

// 무기를 장착/해제할 때의 애니메이션 및 상태 데이터를 담는 구조체
USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName HolsterSocketName;
	
	UPROPERTY(EditAnywhere)
	FName EquipSocketName;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> EquipMontage;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;
};

UCLASS()
class ODYSSEY_API UCWeaponStructures : public UObject
{
	GENERATED_BODY()
};
