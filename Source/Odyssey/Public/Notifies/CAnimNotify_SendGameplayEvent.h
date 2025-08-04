#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "CAnimNotify_SendGameplayEvent.generated.h"

UCLASS()
class ODYSSEY_API UCAnimNotify_SendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()

public:
	// 에디터의 디테일 패널에서 이벤트를 발생시킬 태그를 설정할 수 있도록 변수 생성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayEvent")
	FGameplayTag EventTag;
	
	FString GetNotifyName_Implementation() const override;

	virtual void Notify
	(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference
	) override;
};
