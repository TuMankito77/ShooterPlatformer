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
		SelectNextPatrolPoint(*BlackboardComp, *PatrolPath);
	}


	return EBTNodeResult::Succeeded;
}

void UPatrolPointSelector::SelectNextPatrolPoint(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath)
{
	int NextPatrolPointIndex = 0;

	switch (PointSelectionType)
	{
		case PointSelectionType::IncreaseDecreaseInOrder:
		{
			NextPatrolPointIndex = SelectWithIncreaseDecreaseOrder(BlackboardComp, PatrolPath);
			break;
		}

		case PointSelectionType::IncreaseLoop:
		{
			NextPatrolPointIndex = SelectWithIncreaseLoop(BlackboardComp, PatrolPath);
			break;
		}

		case PointSelectionType::DecreaseLoop:
		{
			NextPatrolPointIndex = SelectWithDecreaseLoop(BlackboardComp, PatrolPath);
			break;
		}

		case PointSelectionType::Random:
		{
			NextPatrolPointIndex = SelectWithRamdom(BlackboardComp, PatrolPath);
			break;
		}

		default:
		{
			break;
		}
	}

	BlackboardComp.SetValueAsVector(FName("TargetLocation"), PatrolPath.GetPatrolPointLocation(FMath::Abs(NextPatrolPointIndex)));
	BlackboardComp.SetValueAsInt(FName("PatrolLocationIndex"), NextPatrolPointIndex);
}

int UPatrolPointSelector::SelectWithIncreaseDecreaseOrder(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath)
{
	int PatrolLocationIndex = BlackboardComp.GetValueAsInt(FName("PatrolLocationIndex"));
	

	
	PatrolLocationIndex--;
	PatrolLocationIndex = PatrolLocationIndex % PatrolPath.PatrolPointLocations.Num();
	return PatrolLocationIndex;
}
int UPatrolPointSelector::SelectWithIncreaseLoop(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath)
{
	bool bIsFirstIteration = BlackboardComp.GetValueAsBool(FName("IsFirstIteration"));

	if (bIsFirstIteration)
	{
		BlackboardComp.SetValueAsBool(FName("IsFirstIteration"), false);
		return 0;
	}

	int PatrolLocationIndex = BlackboardComp.GetValueAsInt(FName("PatrolLocationIndex"));
	PatrolLocationIndex++;
	PatrolLocationIndex %= PatrolPath.PatrolPointLocations.Num();
	return PatrolLocationIndex;
}
int UPatrolPointSelector::SelectWithDecreaseLoop(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath)
{
	bool bIsFirstIteration = BlackboardComp.GetValueAsBool(FName("IsFirstIteration"));
	int PatrolLocationIndex = BlackboardComp.GetValueAsInt(FName("PatrolLocationIndex"));

	if (bIsFirstIteration)
	{
		BlackboardComp.SetValueAsBool(FName("IsFirstIteration"), false);
		return PatrolPath.PatrolPointLocations.Num() - 1;
	}

	PatrolLocationIndex = (PatrolLocationIndex - 1 + PatrolPath.PatrolPointLocations.Num()) % PatrolPath.PatrolPointLocations.Num();
	return PatrolLocationIndex;
}
int UPatrolPointSelector::SelectWithRamdom(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath)
{
	return FMath::RandRange((int)0, (int)PatrolPath.PatrolPointLocations.Num());
}