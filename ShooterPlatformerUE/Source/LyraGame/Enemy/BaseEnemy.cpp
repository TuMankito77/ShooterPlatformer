// All rights reserved to GameBox studios


#include "Enemy/BaseEnemy.h"
#include "LyraGame/AbilitySystem/LyraAbilitySet.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AnimationSetUpComponent.h"
#include "PatrolPath.h"
#include "AbilitySystem/Attributes/LyraCombatSet.h"
#include "LyraGame/Character/LyraHealthComponent.h"
#include "AbilitySystem/Attributes/LyraHealthSet.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemyWidget.h"

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
	HealthComponent->OnHealthChanged.AddDynamic(this, &ABaseEnemy::OnHealthChanged);
	InitializeWidgets();
}

void ABaseEnemy::EndPlay(const EEndPlayReason::Type EndplayReason)
{
	Super::EndPlay(EndplayReason);
	HealthComponent->OnHealthChanged.RemoveDynamic(this, &ABaseEnemy::OnHealthChanged);
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

void ABaseEnemy::OnHealthChanged(ULyraHealthComponent* SourceHealthComponent, float OldValue, float NewValue, AActor* SourceInstigator)
{
	UE_LOG(LogTemp, Display, TEXT("Receiving damage."));
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
			EnemyWidget->OnInitialize();
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
			EnemyWidget->OnDeinitialize();
		}
	}
}