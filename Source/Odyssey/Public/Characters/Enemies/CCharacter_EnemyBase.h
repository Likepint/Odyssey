#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacterBase.h"
#include "Enums/EAIStrategyType.h"
#include "CCharacter_EnemyBase.generated.h"

class UBehaviorTree;

UCLASS()
class ODYSSEY_API ACCharacter_EnemyBase : public ACCharacterBase
{
	GENERATED_BODY()

public:
	ACCharacter_EnemyBase();

	// AI 컨트롤러가 자신에게 맞는 BehaviorTree를 로드할 함수
	UBehaviorTree* GetBehaviorTree();

private:
	// 에디터에서 Enemy의 기본 전략을 선택할 수 있도록 하는 변수
	UPROPERTY(EditAnywhere, Category = "AI")
	EAIStrategyType AIStrategy = EAIStrategyType::Max;

	// 각 전략 타입에 맞는 BehaviorTree Asset을 에디터에서 할당 할 수 있도록 하는 변수
	UPROPERTY(EditAnywhere, Category = "AI")
	TMap<EAIStrategyType, TObjectPtr<UBehaviorTree>> BehaviorTreeMap;
};
