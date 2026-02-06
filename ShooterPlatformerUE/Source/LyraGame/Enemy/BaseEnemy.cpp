// All rights reserved to GameBox studios


#include "Enemy/BaseEnemy.h"

#include "AbilitySystem/LyraAbilitySystemComponent.h"
//#include "GameplayAbilities/Public/AbilitySystemComponent.h"

ABaseEnemy::ABaseEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULyraAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	SetNetUpdateFrequency(100.0f);
}

void ABaseEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
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