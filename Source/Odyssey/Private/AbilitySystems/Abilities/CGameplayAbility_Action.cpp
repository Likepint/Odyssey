#include "AbilitySystems/Abilities/CGameplayAbility_Action.h"
#include "Global.h"
#include "Characters/CCharacterBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"

UCGameplayAbility_Action::UCGameplayAbility_Action()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCGameplayAbility_Action::SetCanAcceptNextCombo(bool bInValue)
{
    bCanAcceptNextCombo = bInValue;
}

void UCGameplayAbility_Action::TryUpdateCombo()
{
	if (bCanAcceptNextCombo)
		bNextComboInputReceived = true;
}

void UCGameplayAbility_Action::ActivateAbility
(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!Montage || ActionData.Num() == 0)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ComboIndex = 0;
	bNextComboInputReceived = false;
	bCanAcceptNextCombo = false;
	
	// 몽타주 재생 태스크는 처음에 한 번만 실행합니다.
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, Montage);
	MontageTask->OnCompleted.AddDynamic(this, &UCGameplayAbility_Action::OnMontageEnded);
	MontageTask->OnInterrupted.AddDynamic(this, &UCGameplayAbility_Action::OnMontageEnded);
	MontageTask->OnCancelled.AddDynamic(this, &UCGameplayAbility_Action::OnMontageEnded);
	MontageTask->ReadyForActivation();

	// 콤보의 첫 번째 단계에 대한 이벤트 대기 태스크들을 실행합니다.
	const FComboActionData& CurrentAction = ActionData[ComboIndex];
	
	UAbilityTask_WaitGameplayEvent* DamageEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, CurrentAction.DamageEventTag);
	DamageEventTask->EventReceived.AddDynamic(this, &UCGameplayAbility_Action::OnDamageEvent);
	DamageEventTask->ReadyForActivation();

	UAbilityTask_WaitGameplayEvent* TransitionEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, CurrentAction.TransitionEventTag);
	TransitionEventTask->EventReceived.AddDynamic(this, &UCGameplayAbility_Action::OnTransitionEvent);
	TransitionEventTask->ReadyForActivation();
}

void UCGameplayAbility_Action::EndAbility
(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled
)
{
	bCanAcceptNextCombo = false;
	bNextComboInputReceived = false;
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UCGameplayAbility_Action::OnMontageEnded()
{
	// 몽타주가 어떤 이유로든 끝나면(콤보 실패 또는 완료), 어빌리티를 종료합니다.
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UCGameplayAbility_Action::OnDamageEvent(FGameplayEventData Payload)
{
	if (!ActionData.IsValidIndex(ComboIndex)) return;
	const FComboActionData& CurrentAction = ActionData[ComboIndex];

	if (!CurrentAction.Effect) return;

	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!Character) return;
    
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Character);
	FHitResult HitResult;

	UKismetSystemLibrary::SphereTraceSingle(
	   Character,
	   Character->GetActorLocation(),
	   Character->GetActorLocation() + Character->GetActorForwardVector() * 200.0f,
	   50.0f,
	   ETraceTypeQuery::TraceTypeQuery1,
	   false,
	   IgnoreActors,
	   EDrawDebugTrace::None,
	   HitResult,
	   true
	);
    
	AActor* TargetActor = HitResult.GetActor();
	if(TargetActor)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (TargetASC)
		{
			FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CurrentAction.Effect);
			FGameplayAbilityTargetDataHandle TargetDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(TargetActor);
			ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), SpecHandle, TargetDataHandle);
		}
	}
}

void UCGameplayAbility_Action::OnTransitionEvent(FGameplayEventData Payload)
{
	if (bNextComboInputReceived)
	{
		bNextComboInputReceived = false;
		const int32 NextComboIndex = ComboIndex + 1;

		if (ActionData.IsValidIndex(NextComboIndex))
		{
			ComboIndex = NextComboIndex;
			const FComboActionData& NextAction = ActionData[ComboIndex];
			
			// 다음 콤보 섹션으로 점프, 섹션 이름은 몽타주에서 'Action01', 'Action02' 등으로 지정
			FName NextSectionName = FName(*FString::Printf(TEXT("Action0%d"), ComboIndex + 1));
			MontageJumpToSection(NextSectionName);

			// 다음 단계의 이벤트를 기다리도록 태스크를 새로 생성
			UAbilityTask_WaitGameplayEvent* DamageEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, NextAction.DamageEventTag);
			DamageEventTask->EventReceived.AddDynamic(this, &UCGameplayAbility_Action::OnDamageEvent);
			DamageEventTask->ReadyForActivation();

			UAbilityTask_WaitGameplayEvent* TransitionEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, NextAction.TransitionEventTag);
			TransitionEventTask->EventReceived.AddDynamic(this, &UCGameplayAbility_Action::OnTransitionEvent);
			TransitionEventTask->ReadyForActivation();
		}
	}
}
