#include "AbilitySystems/AttributeSets/CAttributeSet.h"
#include "Net/UnrealNetwork.h"

UCAttributeSet::UCAttributeSet()
{
}

void UCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UCAttributeSet, CurHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UCAttributeSet::OnRep_CurHealth(const FGameplayAttributeData& OldCurHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, CurHealth, OldCurHealth);
}

void UCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, MaxHealth, OldMaxHealth);
}
