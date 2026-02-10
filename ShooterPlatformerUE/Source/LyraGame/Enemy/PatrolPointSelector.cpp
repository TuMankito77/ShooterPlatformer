// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/PatrolPointSelector.h"

#include "AIControllerBaseEnemy.h"
#include "BaseEnemy.h"
#include "PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UPatrolPointSelector::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AICBaseEnemy = Cast<AAIControllerBaseEnemy>(OwnerComp.GetOwner());
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(AICBaseEnemy->GetPawn());

	if (!IsValid(BaseEnemy))
	{
		return EBTNodeResult::Failed;
	}

	APatrolPath* PatrolPath = BaseEnemy->GetPatrolPath();

	if (!IsValid(PatrolPath) || PatrolPath->PatrolPointLocations.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(FName("TargetLocation"), PatrolPath->GetPatrolPointLocation(0));
	}


	return EBTNodeResult::Succeeded;
}