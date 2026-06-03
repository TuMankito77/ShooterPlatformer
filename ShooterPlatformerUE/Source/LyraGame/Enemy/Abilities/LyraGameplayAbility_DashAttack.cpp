// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/Abilities/LyraGameplayAbility_DashAttack.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Enemy/Abilities/AbilityTask_Tick.h"
#include "GameFramework/RootMotionSource.h"
#include "LyraGame/AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Enemy/BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"

void ULyraGameplayAbility_DashAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	float MontagePlayRate = MontageToPlay->GetPlayLength() / Duration;

	PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy
	(
		this,
		FName("DashAttackPlayMontage"),
		MontageToPlay,
		MontagePlayRate,
		NAME_None,
		true,
		1.0F,
		0.0f
	);

	PlayMontageTask->ReadyForActivation();

	TickTask = UAbilityTask_Tick::CreateTickingAbilityTask(this);
	TickTask->OnTaskTick.AddDynamic(this, &ULyraGameplayAbility_DashAttack::CheckForActorsToDamage);
	TickTask->ReadyForActivation();

	RootMotionTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce
	(
		this,
		FName("DashAttackRootMontion"),
		GetAvatarActorFromActorInfo()->GetActorForwardVector(),
		Streength,
		Duration,
		true,
		nullptr,
		ERootMotionFinishVelocityMode::SetVelocity,
		FVector(0, 0, 0),
		0,
		false
	);

	RootMotionTask->OnFinish.AddDynamic(this, &ULyraGameplayAbility_DashAttack::OnRootMotionTaskFinished);
	RootMotionTask->ReadyForActivation();
}

void ULyraGameplayAbility_DashAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsValid(PlayMontageTask))
	{
		PlayMontageTask->EndTask();
	}

	if (IsValid(TickTask))
	{
		TickTask->OnTaskTick.RemoveDynamic(this, &ULyraGameplayAbility_DashAttack::CheckForActorsToDamage);
		TickTask->EndTask();
	}

	if(IsValid(RootMotionTask))
	{
		RootMotionTask->EndTask();
	}

	AlreadyDamagedActors.Empty();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void ULyraGameplayAbility_DashAttack::OnRootMotionTaskFinished()
{
	RootMotionTask->OnFinish.RemoveDynamic(this, &ULyraGameplayAbility_DashAttack::OnRootMotionTaskFinished);
	const bool bReplicateEndAbility = true;
	const bool bWasCanceled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCanceled);
}

void ULyraGameplayAbility_DashAttack::CheckForActorsToDamage(float DeltaTime)
{
	AActor* OwningActor = GetAvatarActorFromActorInfo();

	if (!IsValid(OwningActor))
	{
		return;
	}

	UCapsuleComponent* CapsuleComponent = OwningActor->GetComponentByClass<UCapsuleComponent>();
	
	if (CapsuleComponent == nullptr)
	{
		return;
	}
	
	TArray<FHitResult> HitResults;
	FVector ActorForwardVector = OwningActor->GetActorForwardVector();
	FVector Start = OwningActor->GetActorLocation() + ActorForwardVector * CapsuleComponent->GetScaledCapsuleRadius();
	FVector End = Start + ActorForwardVector * DashDamageDistance;
	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleComponent->GetScaledCapsuleRadius(), CapsuleComponent->GetScaledCapsuleHalfHeight());
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(OwningActor);
	CollisionQueryParams.AddIgnoredActors(AlreadyDamagedActors);
	bool WasHitDetected = GetWorld()->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, CollisionObjectQueryParams, CapsuleShape, CollisionQueryParams);

	if (WasHitDetected)
	{
		for (FHitResult HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();

			if (AlreadyDamagedActors.Contains(HitActor))
			{
				continue;
			}

			AlreadyDamagedActors.Add(HitActor);

			if (IsDebugginEnabled())
			{
				UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *(HitActor->GetName()));
			}
		}

		if (IsDebugginEnabled())
		{
			DrawDebugCapsule(GetWorld(), Start, CapsuleComponent->GetScaledCapsuleHalfHeight(), CapsuleComponent->GetScaledCapsuleRadius(), FQuat::Identity, ActorsDamagedColor, false, DebugCapsuleVisivilityDuration);
			DrawDebugCapsule(GetWorld(), End, CapsuleComponent->GetScaledCapsuleHalfHeight(), CapsuleComponent->GetScaledCapsuleRadius(), FQuat::Identity, ActorsDamagedColor, false, DebugCapsuleVisivilityDuration);
		}
	}
	else
	{
		if (IsDebugginEnabled())
		{
			DrawDebugCapsule(GetWorld(), Start, CapsuleComponent->GetScaledCapsuleHalfHeight(), CapsuleComponent->GetScaledCapsuleRadius(), FQuat::Identity, NoActorDamagedColor, false, DebugCapsuleVisivilityDuration);
			DrawDebugCapsule(GetWorld(), End, CapsuleComponent->GetScaledCapsuleHalfHeight(), CapsuleComponent->GetScaledCapsuleRadius(), FQuat::Identity, NoActorDamagedColor, false, DebugCapsuleVisivilityDuration);
		}
	}
}