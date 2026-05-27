// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_CapsuleTraceTick.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UAbilityTask_CapsuleTraceTick : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UAbilityTask_CapsuleTraceTick();
	virtual void TickTask(float DeltaTime) override;
	virtual void Activate() override;
	static UAbilityTask_CapsuleTraceTick* CapsuleTraceTick(UGameplayAbility* OwningAbility);

protected:
	virtual void OnDestroy(bool AbilityEnded) override;
	bool IsTicking = true;
};
