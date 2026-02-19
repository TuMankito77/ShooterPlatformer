// Copyright GameBox Studios All Rights Reserved.
#include "Enemy/Debug/EnemyDebugCategory.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

FEnemyDebugCategory::FEnemyDebugCategory()
{
	bShowOnlyWithDebugActor = true;
}

void FEnemyDebugCategory::CollectData(APlayerController* Owner, AActor* DebugActor)
{
	bHasMoveTarget = false;

	if (!IsValid(DebugActor))
	{
		return;
	}

	AAIController* AIController = Cast<AAIController>(DebugActor->GetInstigatorController());

	if (!IsValid(AIController))
	{
		return;
	}

	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	if (!IsValid(BlackboardComponent))
	{
		return;
	}

	PatrolPointLocation = BlackboardComponent->GetValueAsVector("TargetLocation");
	AttackLocation = BlackboardComponent->GetValueAsVector("AttackLocation");
	AttackTarget = Cast<AActor>(BlackboardComponent->GetValueAsObject("AttackTarget"));
	bHasMoveTarget = true;
}

void FEnemyDebugCategory::DrawData(APlayerController* Owner, FGameplayDebuggerCanvasContext& CanvasContext)
{
	if (bHasMoveTarget)
	{
		if (IsValid(AttackTarget))
		{
			DrawDebugSphere(Owner->GetWorld(), AttackLocation, DEBUG_SPHERE_RADIUS, DEBUG_SPHERE_SEGMENTS, FColor::Green, false, 0);
			DrawDebugSphere(Owner->GetWorld(), AttackTarget->GetActorLocation(), DEBUG_SPHERE_RADIUS, DEBUG_SPHERE_SEGMENTS, FColor::Red, false, 0);
		}
		else
		{
			DrawDebugSphere(Owner->GetWorld(), PatrolPointLocation, DEBUG_SPHERE_RADIUS, DEBUG_SPHERE_SEGMENTS, FColor::Blue, false, 0);
			CanvasContext.Printf(TEXT("Current Target Location: %s"), *PatrolPointLocation.ToString());
		}
	}
	else
	{
		CanvasContext.Printf(TEXT("Current Target Location: None"));
	}
}

TSharedRef<FGameplayDebuggerCategory> FEnemyDebugCategory::MakeInstance()
{
	return MakeShareable(new FEnemyDebugCategory());
}