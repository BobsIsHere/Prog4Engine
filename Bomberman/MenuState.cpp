#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "StageState.h"
#include "MenuState.h"

void dae::MenuState::Update()
{
}

void dae::MenuState::Render()
{
}

void dae::MenuState::OnEnter()
{
	SceneManager::GetInstance().SetActiveScene("bombermanMenu");
	dae::AudioServiceLocator::GetAudioSystem().PlayMusic("../Data/Audio/BombermanMenu.wav", 1.f);
}

void dae::MenuState::OnExit()
{
	dae::AudioServiceLocator::GetAudioSystem().StopMusic();
}

dae::GameStateInterface* dae::MenuState::HandleInput()
{
	if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_RETURN))
	{
		return new StageState();
	}

	return nullptr;
}
