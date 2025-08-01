#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_StateUpdate.generated.h"

UCLASS()
class ODYSSEY_API UCAnimNotifyState_StateUpdate : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	                        const FAnimNotifyEventReference& EventReference);
};
