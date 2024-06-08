#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "SceneManager.h"
#include "PlayingState.h"
#include "StageState.h"
#include "DeltaTime.h"
#include "Renderer.h"

dae::StageState::StageState() :
	m_StageNumber{ 1 },
	m_SwitchingStateTimer{ 3.f }
{
}

dae::StageState::~StageState()
{
}

void dae::StageState::Update()
{
	m_SwitchingStateTimer -= DeltaTime::GetInstance().GetDeltaTime(); 
}

void dae::StageState::Render()
{
}

void dae::StageState::OnEnter()
{
	SceneManager::GetInstance().SetActiveScene("bombermanStage");

	// Set backrgound to black
	Renderer::GetInstance().SetBackgroundColor(SDL_Color{ 0, 0, 0, 255 }); 
	dae::AudioServiceLocator::GetAudioSystem().PlayMusic("../Data/Audio/StageStart.mp3", 1.f);
}

void dae::StageState::OnExit() 
{ 
	dae::AudioServiceLocator::GetAudioSystem().StopMusic(); 
}

dae::GameStateInterface* dae::StageState::HandleInput() 
{
	if (m_SwitchingStateTimer <= 0.f)
	{
		return new PlayingState(); 
	}

	return nullptr;
}
