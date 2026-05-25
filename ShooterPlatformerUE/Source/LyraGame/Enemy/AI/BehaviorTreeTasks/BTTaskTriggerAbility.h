// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagcontainer.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "BTTaskTriggerAbility.generated.h"

class ABaseEnemy;

UCLASS()
class LYRAGAME_API UBTTaskTriggerAbility : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CachedBehaviorTreeComp = nullptr;

	UPROPERTY()
	TObjectPtr<ABaseEnemy> CachedBaseEnemy = nullptr;

	UFUNCTION()
	void OnAbilityFinished();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AbilityToTrigger = FGameplayTag();

public:
	UBTTaskTriggerAbility();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
