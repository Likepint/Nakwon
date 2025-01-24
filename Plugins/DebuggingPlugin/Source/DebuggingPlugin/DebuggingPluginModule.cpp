#include "DebuggingPluginModule.h"
#include "CharacterDebuggerCategory.h"

#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "FDebuggingPluginModule"

IMPLEMENT_MODULE(FDebuggingPluginModule, DebuggingPlugin)

void FDebuggingPluginModule::StartupModule()
{
	IGameplayDebugger::FOnGetCategory category;
	category.BindStatic(CharacterDebuggerCategory::MakeInstance);

	IGameplayDebugger::Get().RegisterCategory("Character", category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
	IGameplayDebugger::Get().NotifyCategoriesChanged();
}

void FDebuggingPluginModule::ShutdownModule()
{
	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("Character");
}

#undef LOCTEXT_NAMESPACE
