// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolPointSelector.generated.h"

class AAIControllerBaseEnemy;
class APatrolPath;

UENUM()
enum class PointSelectionType
{
	IncreaseDecreaseInOrder UMETA(DisplayName = "Increase Decrease in order"),
	IncreaseLoop UMETA(DisplayName = "Increase loop"),
	DecreaseLoop UMETA(DisplayName = "Decrease loop"),
	Random UMETA(DisplayName = "Random")
};

UCLASS()
class LYRAGAME_API UPatrolPointSelector : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	PointSelectionType PointSelectionType = PointSelectionType::IncreaseDecreaseInOrder;

	TObjectPtr<AAIControllerBaseEnemy> AICBaseEnemy = nullptr;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	void SelectNextPatrolPoint(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath);
	int SelectWithIncreaseDecreaseOrder(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath);
	int SelectWithIncreaseLoop(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath);
	int SelectWithDecreaseLoop(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath);
	int SelectWithRamdom(UBlackboardComponent& BlackboardComp, APatrolPath& PatrolPath);
};
