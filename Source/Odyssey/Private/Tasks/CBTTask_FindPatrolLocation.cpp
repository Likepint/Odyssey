#include "Tasks/CBTTask_FindPatrolLocation.h"

#include "AIController.h"
#include "Global.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTask_FindPatrolLocation::UCBTTask_FindPatrolLocation()
{
	NodeName = "Find Patrol Location";
}

EBTNodeResult::Type UCBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	CheckNullResult(pawn, EBTNodeResult::Failed);

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	CheckNullResult(navSystem, EBTNodeResult::Failed);

	FNavLocation nextPatrolLocation;
	if (navSystem->GetRandomPointInNavigableRadius(pawn->GetActorLocation(), PatrolRadius, nextPatrolLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolLocationKey.SelectedKeyName,
		                                                     nextPatrolLocation.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
