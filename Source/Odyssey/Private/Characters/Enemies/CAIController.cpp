#include "Characters/Enemies/CAIController.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/CCharacter_EnemyBase.h"

ACAIController::ACAIController()
{
	CHelpers::CreateActorComponent(this, BehaviorTreeComponent, TEXT("BehaviorTreeComponent"));
	CHelpers::CreateActorComponent(this, BlackboardComponent, TEXT("BlackboardComponent"));
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ACCharacter_EnemyBase* enemy = Cast<ACCharacter_EnemyBase>(InPawn);
	CheckNull(enemy);

	UBehaviorTree* behaviorTree = enemy->GetBehaviorTree();
	CheckNull(behaviorTree);

	BlackboardComponent->InitializeBlackboard(*(behaviorTree->BlackboardAsset));
	BehaviorTreeComponent->StartTree(*behaviorTree);
}
