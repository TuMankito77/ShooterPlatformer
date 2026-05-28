// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_Tick.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UAbilityTask_Tick : public UAbilityTask
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskTick, float, DeltaTime);
	
public:
	FOnTaskTick OnTaskTick;

	virtual void TickTask(float DeltaTime) override;
	virtual void Activate() override;
	static UAbilityTask_Tick* CreateTickingAbilityTask(UGameplayAbility* OwningAbility);

protected:
	virtual void OnDestroy(bool WasAbilityEnded) override;
};
