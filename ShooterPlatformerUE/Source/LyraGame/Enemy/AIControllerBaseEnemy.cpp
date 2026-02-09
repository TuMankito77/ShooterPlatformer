// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/AIControllerBaseEnemy.h"

#include "BaseEnemy.h"

void AAIControllerBaseEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BaseEnemy = Cast<ABaseEnemy>(InPawn);

	if (!IsValid(BaseEnemy))
	{
		return;
	}

	if (IsValid(BaseEnemy->GetBehaviorTree()))
	{
		RunBehaviorTree(BaseEnemy->GetBehaviorTree());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - %s - %s: Does not have a valid behavior tree assigned. Hense, it will do nothing!"), *BaseEnemy->GetName(), *GetName(), ANSI_TO_TCHAR(__FUNCTION__));
	}
}
