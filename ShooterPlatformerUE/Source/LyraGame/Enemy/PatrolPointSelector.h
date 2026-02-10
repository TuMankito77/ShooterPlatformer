// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolPointSelector.generated.h"

class AAIControllerBaseEnemy;

UCLASS()
class LYRAGAME_API UPatrolPointSelector : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	TObjectPtr<AAIControllerBaseEnemy> AICBaseEnemy = nullptr;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
