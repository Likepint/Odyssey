#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CWeaponComponent.h"
#include "CAnimInstanceBase.generated.h"

class ACCharacterBase;

UCLASS()
class ODYSSEY_API UCAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<ACCharacterBase> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float Acceleration = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCrouched = false;

	// 애님 그래프에서 사용할 무기 타입 변수
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	EWeaponType WeaponType = EWeaponType::Max;

private:
	UFUNCTION()
	void OnWeaponTypeChanged(EWeaponType InNewType);
};
