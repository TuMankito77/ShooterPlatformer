// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/AI/BehaviorTreeTasks/BTTaskTriggerAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Enemy/AIControllerBaseEnemy.h"
#include "Enemy/BaseEnemy.h"

EBTNodeResult::Type UBTTaskTriggerAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIControllerBaseEnemy* AICBaseEnemy = Cast<AAIControllerBaseEnemy>(OwnerComp.GetOwner());
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(AICBaseEnemy->GetPawn());
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BaseEnemy, AbilityToTrigger, FGameplayEventData());
	return EBTNodeResult::Succeeded;
}