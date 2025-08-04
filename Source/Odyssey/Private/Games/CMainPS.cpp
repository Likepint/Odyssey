#include "Games/CMainPS.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystems/AttributeSets/CAttributeSet.h"

ACMainPS::ACMainPS()
{
	CHelpers::CreateActorComponent<UAbilitySystemComponent>(this, AbilitySystemComponent, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	
	CHelpers::CreateActorComponent<UCAttributeSet>(this, AttributeSet, TEXT("AttributeSet"));

	SetNetUpdateFrequency(100.0f);
}

UAbilitySystemComponent* ACMainPS::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
