#include "LevelCompleteState.h"
#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "StageState.h"
#include "DeltaTime.h"

void dae::LevelCompleteState::Update()
{
	m_AccumulatedTime += dae::DeltaTime::GetInstance().GetDeltaTime();
}

void dae::LevelCompleteState::Render()
{
}

void dae::LevelCompleteState::OnEnter()
{
	dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/LevelFinished.mp3", 0.5f);
}

void dae::LevelCompleteState::OnExit()
{
	dae::AudioServiceLocator::GetAudioSystem().StopMusic();
}

dae::GameStateInterface* dae::LevelCompleteState::HandleInput()
{
	if (m_TimeToWait <= m_AccumulatedTime)
	{
		return new StageState();
	}

	return nullptr;
}
