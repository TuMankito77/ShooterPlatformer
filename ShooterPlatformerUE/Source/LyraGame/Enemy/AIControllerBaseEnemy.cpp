// Copyright GameBox Studios All Rights Reserved.
#include "Enemy/AIControllerBaseEnemy.h"

#include "BaseEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIControllerBaseEnemy::AAIControllerBaseEnemy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AIPerceptionComponent = ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("AIPerception"));

	TArray<UAISenseConfig*> SenseConfigs = 
	{
		ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Sight>(this, TEXT("SightConfig")),
		ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Hearing>(this, TEXT("HearingConfig")),
		ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Damage>(this, TEXT("DamageConfig"))
	};

	for (UAISenseConfig* SenseConfig : SenseConfigs)
	{
		AIPerceptionComponent->ConfigureSense(*SenseConfig);
	}
}

void AAIControllerBaseEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BaseEnemy = Cast<ABaseEnemy>(InPawn);

	if (!IsValid(BaseEnemy))
	{
		return;
	}

	if (IsValid(BaseEnemy->GetBehaviorTree()))
	{
		RunBehaviorTree(BaseEnemy->GetBehaviorTree());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - %s - %s: Does not have a valid behavior tree assigned. Hense, it will do nothing!"), *BaseEnemy->GetName(), *GetName(), ANSI_TO_TCHAR(__FUNCTION__));
	}

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAIControllerBaseEnemy::OnPerceptionUpdated);
}

void AAIControllerBaseEnemy::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* UpdatedActor : UpdatedActors)
	{
		UE_LOG(LogTemp, Display, TEXT("%s - %s - %s: %s!"), *BaseEnemy->GetName(), *GetName(), ANSI_TO_TCHAR(__FUNCTION__), *(UpdatedActor->GetName()));
	}

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (!BlackboardComponent)
	{
		return;
	}

	AActor* AttackTarget = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName("AttackTarget")));

	if (!IsValid(AttackTarget))
	{
		AActor* NewAttackTarget = UpdatedActors[FMath::RandRange((int)0, (int)(UpdatedActors.Num() - 1))];
		BlackboardComponent->SetValueAsObject(FName("AttackTarget"), NewAttackTarget);
	}
}
