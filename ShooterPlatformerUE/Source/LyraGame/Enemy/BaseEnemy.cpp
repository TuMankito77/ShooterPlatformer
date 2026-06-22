// All rights reserved to GameBox studios


#include "Enemy/BaseEnemy.h"
#include "LyraGame/AbilitySystem/LyraAbilitySet.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AnimationSetUpComponent.h"
#include "PatrolPath.h"
#include "AbilitySystem/Attributes/LyraCombatSet.h"
#include "LyraGame/Character/LyraHealthComponent.h"
#include "AbilitySystem/Attributes/LyraHealthSet.h"
#include "AbilitySystem/LyraAbilityTagRelationshipMapping.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemyWidget.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AIControllerBaseEnemy.h"

ABaseEnemy::ABaseEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULyraAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AnimationSetUpComponent = ObjectInitializer.CreateDefaultSubobject<UAnimationSetUpComponent>(this, TEXT("AnimationSetUpComponent"));
	CombatSet = ObjectInitializer.CreateDefaultSubobject<ULyraCombatSet>(this, TEXT("CombatSet"));
	HealthSet = ObjectInitializer.CreateDefaultSubobject<ULyraHealthSet>(this, TEXT("HealthSet"));
	HealthComponent = ObjectInitializer.CreateDefaultSubobject<ULyraHealthComponent>(this, TEXT("HealthComponent"));

	SetNetUpdateFrequency(100.0f);
}

void ABaseEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	check(AbilitySystemComponent);
	AbilitySystemComponent->SetTagRelationshipMapping(TagRelationshipMapping);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (IsValid(AbilitySet))
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
	}

	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
	SetStartingAnimationLayer();
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	DeathGameplayEvent = UAbilityAsync_WaitGameplayEvent::WaitGameplayEventToActor(this, DeathGameplayTag, true, true);
	DeathGameplayEvent->EventReceived.AddDynamic(this, &ABaseEnemy::OnDeathGameplayEvent);
	//We are casting the event so that it gives us access to the Activate function which is only public in the parent class.
	//If this is not done and the activate is not called, then the event will never trigger the EventReceived callback. 
	UBlueprintAsyncActionBase* DeathGameplayEventAsBPAsyncActionBase = Cast<UBlueprintAsyncActionBase>(DeathGameplayEvent);
	DeathGameplayEventAsBPAsyncActionBase->Activate();
	HealthComponent->OnDeathFinished.AddDynamic(this, &ABaseEnemy::OnDeathFinished);
	InitializeWidgets();
}

void ABaseEnemy::EndPlay(const EEndPlayReason::Type EndplayReason)
{
	Super::EndPlay(EndplayReason);
	DeathGameplayEvent->EventReceived.RemoveDynamic(this, &ABaseEnemy::OnDeathGameplayEvent);
	DeinitializeWidgets();
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

FGenericTeamId ABaseEnemy::GetGenericTeamId() const
{
	return IntegerToGenericTeamId(TeamID);
}

void ABaseEnemy::InitializeWidgets()
{
	TArray<UWidgetComponent*> WidgetComponents;
	GetComponents<UWidgetComponent>(WidgetComponents);

	for (UWidgetComponent* WidgetComponent : WidgetComponents)
	{
		if (IsValid(WidgetComponent->GetWidget()) && WidgetComponent->GetWidget()->IsA<UEnemyWidget>())
		{
			UEnemyWidget* EnemyWidget = Cast<UEnemyWidget>(WidgetComponent->GetWidget());
			EnemyWidget->OnInitialize(this);
		}
	}
}

void ABaseEnemy::DeinitializeWidgets()
{
	TArray<UWidgetComponent*> WidgetComponents;
	GetComponents<UWidgetComponent>(WidgetComponents);

	for (UWidgetComponent* WidgetComponent : WidgetComponents)
	{
		if (IsValid(WidgetComponent->GetWidget()) && WidgetComponent->GetWidget()->IsA<UEnemyWidget>())
		{
			UEnemyWidget* EnemyWidget = Cast<UEnemyWidget>(WidgetComponent->GetWidget());
			EnemyWidget->OnDeinitialize(this);
		}
	}
}

void ABaseEnemy::OnDeathGameplayEvent(FGameplayEventData Payload)
{
	AAIControllerBaseEnemy*  AIControllerBaseEnemy = Cast<AAIControllerBaseEnemy>(GetController());
	AIControllerBaseEnemy->BrainComponent->StopLogic(TEXT("Enemy Death"));
}

void ABaseEnemy::OnDeathFinished(AActor* OwningActor)
{
	HealthComponent->OnDeathFinished.RemoveDynamic(this, &ABaseEnemy::OnDeathFinished);
	Destroy();
}