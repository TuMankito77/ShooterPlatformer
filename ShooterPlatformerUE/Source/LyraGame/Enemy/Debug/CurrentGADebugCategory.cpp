// Copyright GameBox Studios All Rights Reserved.

#include "Enemy/Debug/CurrentGADebugCategory.h"

TWeakObjectPtr<AActor> FCurrentGADebugCategory::CurrentDebugActor = nullptr;

FCurrentGADebugCategory::FCurrentGADebugCategory()
{

}

void FCurrentGADebugCategory::CollectData(APlayerController* Owner, AActor* DebugActor)
{
	CurrentDebugActor = DebugActor;
}

void FCurrentGADebugCategory::OnDeactivated()
{
	CurrentDebugActor = nullptr;
}

TSharedRef<FGameplayDebuggerCategory> FCurrentGADebugCategory::MakeInstance()
{
	return MakeShareable(new FCurrentGADebugCategory());
}