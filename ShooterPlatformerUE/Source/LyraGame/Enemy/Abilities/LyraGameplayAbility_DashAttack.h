// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LyraGameplayAbility_BTTAbility.h"
#include "GameplayTagcontainer.h"
#include "LyraGameplayAbility_DashAttack.generated.h"

class UAbilityTask_ApplyRootMotionConstantForce;
class UAbilityTask_PlayMontageAndWait;
class UAbilityTask_Tick;
/**
 * 
 */
UCLASS()
class LYRAGAME_API ULyraGameplayAbility_DashAttack : public ULyraGameplayAbility_BTTAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float Streength = 500.0f;

	UPROPERTY(EditAnywhere)
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float DashDamageDistance = 200.0f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> MontageToPlay = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilityTask_ApplyRootMotionConstantForce> RootMotionTask = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilityTask_PlayMontageAndWait> PlayMontageTask = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilityTask_Tick> TickTask = nullptr;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	UFUNCTION()
	void OnRootMotionTaskFinished();

	UFUNCTION()
	void CheckForActorsToDamage(float DeltaTime);
};
