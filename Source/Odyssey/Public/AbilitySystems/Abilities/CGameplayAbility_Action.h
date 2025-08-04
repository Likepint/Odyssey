#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CGameplayAbility_Action.generated.h"

// FComboActionData 구조체 수정
USTRUCT(BlueprintType)
struct FComboActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> Effect;

	UPROPERTY(EditAnywhere)
	FGameplayTag DamageEventTag;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag TransitionEventTag;
};

UCLASS()
class ODYSSEY_API UCGameplayAbility_Action : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCGameplayAbility_Action();

	// AnimNotifyState와 WeaponComponent에서 호출할 함수들
	void SetCanAcceptNextCombo(bool bInValue);
	void TryUpdateCombo();

protected:
	// 사용할 단일 콤보 몽타주
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TObjectPtr<UAnimMontage> Montage;

	// 각 콤보 단계별 데이터 배열
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TArray<FComboActionData> ActionData;

	// 어빌리티가 활성화될 때 호출될 함수
	virtual void ActivateAbility
	(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	// 어빌리티가 종료될 때 호출될 함수
	virtual void EndAbility
	(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled
	) override;

private:
	int32 ComboIndex;
	bool bCanAcceptNextCombo;
	bool bNextComboInputReceived;
	
	// 몽타주가 어떤 이유로든 종료될 때(콤보 실패 또는 완료) 호출될 함수
	UFUNCTION()
	void OnMontageEnded();

	// 타격 판정 이벤트 수신 함수
	UFUNCTION()
	void OnDamageEvent(FGameplayEventData Payload);

	// 다음 콤보로 전환하라는 신호를 받았을 때 호출될 함수
	UFUNCTION()
	void OnTransitionEvent(FGameplayEventData Payload);
};
