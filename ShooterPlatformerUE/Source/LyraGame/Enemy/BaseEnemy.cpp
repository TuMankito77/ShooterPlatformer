// All rights reserved to GameBox studios


#include "Enemy/BaseEnemy.h"

#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AnimationSetUpComponent.h"
#include "PatrolPath.h"

ABaseEnemy::ABaseEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULyraAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AnimationSetUpComponent = ObjectInitializer.CreateDefaultSubobject<UAnimationSetUpComponent>(this, TEXT("AnimationSetUpComponent"));

	SetNetUpdateFrequency(100.0f);
}

void ABaseEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	SetStartingAnimationLayer();
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ULyraAbilitySystemComponent* ABaseEnemy::GetLyraAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAbilitySystemComponent* ABaseEnemy::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseEnemy::SetStartingAnimationLayer()
{
	AnimationSetUpComponent->UpdateLinkedAnimClassLayer(AnimationSetUpComponent->GetDefaultAnimLayer());
}

UBehaviorTree* ABaseEnemy::GetBehaviorTree()
{
	return BehaviorTree;
}

APatrolPath* ABaseEnemy::GetPatrolPath()
{
	return PatrolPath;
}