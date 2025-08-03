#include "Characters/Enemies/CCharacter_EnemyBase.h"
#include "Global.h"

ACCharacter_EnemyBase::ACCharacter_EnemyBase()
{
	// Enemy가 사용할 AI Controller 지정
	// AIControllerClass =
}

UBehaviorTree* ACCharacter_EnemyBase::GetBehaviorTree()
{
	if (BehaviorTreeMap.Contains(AIStrategy))
	{
		return BehaviorTreeMap[AIStrategy];
	}

	return nullptr;
}
