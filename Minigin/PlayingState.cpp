#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "PlayingState.h"

void dae::PlayingState::Update()
{
}

void dae::PlayingState::Render()
{
}

void dae::PlayingState::OnEnter()
{
	dae::AudioServiceLocator::GetAudioSystem().PlayMusic("../Data/Audio/LevelBackground.mp3", 1.f);
}

void dae::PlayingState::OnExit()
{
	dae::AudioServiceLocator::GetAudioSystem().StopMusic(); 
}

dae::GameStateInterface* dae::PlayingState::HandleInput()
{
	return nullptr;
}
