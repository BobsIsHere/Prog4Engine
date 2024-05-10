#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "PlayingState.h"
#include "HighscoreState.h"

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
}

void dae::PlayingState::OnExit()
{
	dae::AudioServiceLocator::GetAudioSystem().StopMusic(); 
}

dae::GameStateInterface* dae::PlayingState::HandleInput()
{
	if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_H))
	{
		return new HighscoreState(); 
	}

	return nullptr;
}
