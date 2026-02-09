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
	Super::PostInitializeComponents();

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

	UE_LOG(LogTemp, Error, TEXT("%s - %s: The index for the patrol path point location is ivalid, the value returned will be the world center location."), *GetName(), ANSI_TO_TCHAR(__FUNCTION__));
	return FVector(0, 0, 0);
}

#if WITH_EDITOR

void APatrolPath::ShowPatrolPointsInLevel()
{
	//If we are in game, this array will get populated. 
	if (PatrolPointLocations.Num() > 0)
	{
		int index = 0;

		for (FVector Location : PatrolPointLocations)
		{
			DrawDebugSphere(GetWorld(), Location, 50.0f, 12, FColor::Blue, false, 5, (uint8)0U, 5);
			UE_LOG(LogTemp, Log, TEXT("%s-%s: Patrol point %d - Location %s"), *GetName(), ANSI_TO_TCHAR(__FUNCTION__), index, *Location.ToString());
			index++;
		}

		return;
	}

	//If not in game, we just grab the values from the spline itself. 
	for (int i = 0; i < PatrolPoints->GetNumberOfSplinePoints(); i++)
	{
		FVector Location = PatrolPoints->GetSplinePointAt(i, ESplineCoordinateSpace::World).Position;
		DrawDebugSphere(GetWorld(), Location, 50.0f, 12, FColor::Blue, false, 5, (uint8)0U, 5);
		UE_LOG(LogTemp, Log, TEXT("%s-%s: Patrol point %d - Location %s"), *GetName(), ANSI_TO_TCHAR(__FUNCTION__), i, *Location.ToString());
	}
}

#endif

