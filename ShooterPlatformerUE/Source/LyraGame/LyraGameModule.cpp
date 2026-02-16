// Copyright Epic Games, Inc. All Rights Reserved.

#include "Modules/ModuleManager.h"
#if WITH_GAMEPLAY_DEBUGGER
#include "Enemy/Debug/EnemyDebugCategory.h"
#include "GameplayDebugger.h"
#endif

/**
 * FLyraGameModule
 */
class FLyraGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
#if WITH_GAMEPLAY_DEBUGGER
		IGameplayDebugger& Debugger = IGameplayDebugger::Get();
		
		Debugger.RegisterCategory
		(
			"Enemy Movement",
			IGameplayDebugger::FOnGetCategory::CreateStatic(&FEnemyDebugCategory::MakeInstance),
			EGameplayDebuggerCategoryState::EnabledInGameAndSimulate
		);
		
		Debugger.NotifyCategoriesChanged();
#endif
	}

	virtual void ShutdownModule() override
	{
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FLyraGameModule, LyraGame, "LyraGame");
