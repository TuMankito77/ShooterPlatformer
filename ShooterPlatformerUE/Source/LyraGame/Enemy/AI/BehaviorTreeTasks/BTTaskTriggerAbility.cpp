// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/AI/BehaviorTreeTasks/BTTaskTriggerAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Enemy/AIControllerBaseEnemy.h"
#include "Enemy/BaseEnemy.h"

UBTTaskTriggerAbility::UBTTaskTriggerAbility()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskTriggerAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedBehaviorTreeComp = OwnerComp;

	AAIControllerBaseEnemy* AICBaseEnemy = Cast<AAIControllerBaseEnemy>(OwnerComp.GetOwner());

	if (!IsValid(AICBaseEnemy))
	{
		return EBTNodeResult::Failed;
	}

	CachedBaseEnemy = Cast<ABaseEnemy>(AICBaseEnemy->GetPawn());

	if (!IsValid(CachedBaseEnemy))
	{
		return EBTNodeResult::Failed;
	}

	CachedBaseEnemy->OnAbilityExecutionFinished.AddDynamic(this, &UBTTaskTriggerAbility::OnAbilityFinished);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(CachedBaseEnemy, AbilityToTrigger, FGameplayEventData());
	return EBTNodeResult::InProgress;
}

void UBTTaskTriggerAbility::OnAbilityFinished()
{
	if (!IsValid(CachedBehaviorTreeComp))
	{
		return;
	}
	
	if (!IsValid(CachedBaseEnemy))
	{
		return;
	}

	CachedBaseEnemy->OnAbilityExecutionFinished.RemoveDynamic(this, &UBTTaskTriggerAbility::OnAbilityFinished);
	FinishLatentTask(*CachedBehaviorTreeComp, EBTNodeResult::Succeeded);
}