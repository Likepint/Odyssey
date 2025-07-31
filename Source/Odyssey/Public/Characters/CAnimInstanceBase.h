#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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
	bool bIsCrouched = false;
};
