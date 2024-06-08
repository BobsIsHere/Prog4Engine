#include "AudioServiceLocator.h"
#include "LevelCompleteState.h"
#include "GameAudioSystem.h"
#include "HighscoreState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "PlayingState.h"
#include "Renderer.h"

void dae::PlayingState::Update()
{
}

void dae::PlayingState::Render()
{
}

void dae::PlayingState::OnEnter()
{
	SceneManager::GetInstance().SetActiveScene("bombermanGame");
	dae::AudioServiceLocator::GetAudioSystem().PlayMusic("../Data/Audio/LevelBackground.mp3", 1.f);
	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{ 190, 190, 190, 255 });
}

void dae::PlayingState::OnExit()
{
	dae::AudioServiceLocator::GetAudioSystem().StopMusic(); 
}

dae::GameStateInterface* dae::PlayingState::HandleInput()
{
	if (IsWinConditionMet())
	{
		return new dae::LevelCompleteState;
	}

	return nullptr;
}

bool dae::PlayingState::IsWinConditionMet() const
{

	return false;
}
