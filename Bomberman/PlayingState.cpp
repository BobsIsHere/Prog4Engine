#include "AudioServiceLocator.h"
#include "LevelCompleteState.h"
#include "GameAudioSystem.h"
#include "HighscoreState.h"
#include "PlayingState.h"
#include "EnemyManager.h"
#include "Renderer.h"
#include "Scene.h"

dae::PlayingState::PlayingState()
{
}

void dae::PlayingState::Update()
{
}

void dae::PlayingState::Render()
{
}

void dae::PlayingState::OnEnter()
{
	dae::AudioServiceLocator::GetAudioSystem().PlayMusic("../Data/Audio/LevelBackground.mp3", 1.f);
	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{ 190, 190, 190, 255 });

	auto& scenemanager = dae::SceneManager::GetInstance();
	const auto prevScene = SceneManager::GetInstance().GetPreviousScene()->GetSceneName(); 

	dae::SceneManager::GetInstance().SetActiveScene(scenemanager.GetNextScene(prevScene).GetSceneName());
}

void dae::PlayingState::OnExit()
{
	dae::AudioServiceLocator::GetAudioSystem().StopMusic(); 
}

dae::GameStateInterface* dae::PlayingState::HandleInput()
{
	if (IsWinConditionMet())
	{
		return new dae::LevelCompleteState();
	}

	return nullptr;
}

bool dae::PlayingState::IsWinConditionMet() const
{
	auto& enemyManager = dae::EnemyManager::GetInstance();
	return enemyManager.AllEnemiesDead();
}
