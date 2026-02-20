// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LyraGameplayAbility.h"
#include "LyraGameplayAbility_DashAttack.generated.h"

class UAbilityTask_ApplyRootMotionConstantForce;
/**
 * 
 */
UCLASS()
class LYRAGAME_API ULyraGameplayAbility_DashAttack : public ULyraGameplayAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float Streength = 500.0f;

	UPROPERTY(EditAnywhere)
	float Duration = 3.0f;

	UAbilityTask_ApplyRootMotionConstantForce* RootMotionTask = nullptr;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
private:
	void OnRootMotionTaskFinished();
};
