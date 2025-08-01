#pragma once

#include "CoreMinimal.h"
#include "Characters/CAnimInstanceBase.h"
#include "CAnimInstance_Misthios.generated.h"

UCLASS()
class ODYSSEY_API UCAnimInstance_Misthios : public UCAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	float SpeedAtStop = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	bool bWantsToStop = false;
};
