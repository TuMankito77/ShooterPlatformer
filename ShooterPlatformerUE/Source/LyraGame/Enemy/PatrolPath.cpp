// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/PatrolPath.h"
#include "Components/SplineComponent.h"
#include "Components/BillboardComponent.h"

APatrolPath::APatrolPath(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PathVisial = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(this, TEXT("PathVisual"));
	RootComponent = PathVisial;
	PathVisial->bHiddenInGame = false;
	PatrolPoints = ObjectInitializer.CreateDefaultSubobject<USplineComponent>(this, TEXT("Patrol Points"));
	PatrolPoints->SetupAttachment(RootComponent);
}

void APatrolPath::PostInitializeComponents()
{
	for (int i = 0; i < PatrolPoints->GetNumberOfSplinePoints(); i++)
	{
		PatrolPointLocations.Add(PatrolPoints->GetSplinePointAt(i, ESplineCoordinateSpace::World).Position);
	}
}

int APatrolPath::GetPatrolPointsLength()
{
	return PatrolPoints->GetNumberOfSplinePoints();
}

FVector APatrolPath::GetPatrolPointLocation(int Index)
{
	if (PatrolPointLocations.IsValidIndex(Index))
	{
		return PatrolPointLocations[Index];
	}

	UE_LOG(LogTemp, Error, TEXT("%s - %s: The index for the patrol path point location is ivalid, the value returned will be the world center location."), ANSI_TO_TCHAR(__FUNCTION__), *GetName());
	return FVector(0, 0, 0);
}

