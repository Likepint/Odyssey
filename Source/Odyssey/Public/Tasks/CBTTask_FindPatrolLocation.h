#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTask_FindPatrolLocation.generated.h"

UCLASS()
class ODYSSEY_API UCBTTask_FindPatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTask_FindPatrolLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector PatrolLocationKey;
	
	UPROPERTY(EditAnywhere, Category = "Patrol")
	float PatrolRadius = 500.0f;
};
