#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "InputManager.h"
#include "MenuState.h"

void dae::MenuState::Update()
{
}

void dae::MenuState::Render()
{
}

void dae::MenuState::OnEnter()
{
	dae::AudioServiceLocator::GetAudioSystem().PlayMusic("../Data/Audio/BombermanMenu.wav", 1.f);
}

void dae::MenuState::OnExit()
{
	dae::AudioServiceLocator::GetAudioSystem().StopMusic();
}

dae::GameStateInterface* dae::MenuState::HandleInput()
{
	return nullptr;
}
