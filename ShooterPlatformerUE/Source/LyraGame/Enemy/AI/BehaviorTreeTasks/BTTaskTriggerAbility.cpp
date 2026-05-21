// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/AI/BehaviorTreeTasks/BTTaskTriggerAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Enemy/AIControllerBaseEnemy.h"
#include "Enemy/BaseEnemy.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"

UBTTaskTriggerAbility::UBTTaskTriggerAbility()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskTriggerAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedBehaviorTreeComp = OwnerComp;

	AAIControllerBaseEnemy* AICBaseEnemy = Cast<AAIControllerBaseEnemy>(OwnerComp.GetOwner());
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(AICBaseEnemy->GetPawn());
	
	UAbilityAsync_WaitGameplayEvent* EventTask = UAbilityAsync_WaitGameplayEvent::WaitGameplayEventToActor
	(
		BaseEnemy,
		AbilityFinishedTag,
		true,
		true
	);

	EventTask->EventReceived.AddDynamic(this, &UBTTaskTriggerAbility::OnAbilityFinished);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BaseEnemy, AbilityToTrigger, FGameplayEventData());
	return EBTNodeResult::InProgress;
}

void UBTTaskTriggerAbility::OnAbilityFinished(FGameplayEventData Payload)
{
	if (!IsValid(CachedBehaviorTreeComp))
	{
		return;
	}

	FinishLatentTask(*CachedBehaviorTreeComp, EBTNodeResult::Succeeded);
}