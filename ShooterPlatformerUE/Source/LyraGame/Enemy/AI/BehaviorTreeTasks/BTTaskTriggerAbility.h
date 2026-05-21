// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagcontainer.h"
#include "BTTaskTriggerAbility.generated.h"

UCLASS()
class LYRAGAME_API UBTTaskTriggerAbility : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CachedBehaviorTreeComp = nullptr;

	UFUNCTION()
	void OnAbilityFinished(FGameplayEventData Payload);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AbilityToTrigger = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AbilityFinishedTag = FGameplayTag();

public:
	UBTTaskTriggerAbility();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
