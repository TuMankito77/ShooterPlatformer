// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LyraGameplayAbility.h"
#include "LyraGameplayAbility_EnemyDeath.generated.h"

class UAbilityTask_PlayMontageAndWait;

UCLASS()
class LYRAGAME_API ULyraGameplayAbility_EnemyDeath : public ULyraGameplayAbility
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	int DeathDuration = 3;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag DeathGameplayCueTag;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilityTask_PlayMontageAndWait> PlayMontageTask = nullptr;

	FTimerHandle DeathDurationTimer;
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicatedEndAbility, bool bWasCancelled) override;
	void OnDeathDurationTimerCompleted();
};
