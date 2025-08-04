#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "CMainPS.generated.h"

class UAbilitySystemComponent;
class UCAttributeSet;

UCLASS()
class ODYSSEY_API ACMainPS
	: public APlayerState
	, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ACMainPS();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UCAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UCAttributeSet> AttributeSet;
};
