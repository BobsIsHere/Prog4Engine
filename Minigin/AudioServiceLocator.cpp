#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "AudioSystem.h"

std::unique_ptr<dae::AudioSystem> dae::AudioServiceLocator::m_ASInstance = nullptr;

dae::AudioSystem& dae::AudioServiceLocator::GetAudioSystem()
{
	return *m_ASInstance;
}

void dae::AudioServiceLocator::RegisterSoundSystem(std::unique_ptr<AudioSystem>&& ASInstance)
{
	if (ASInstance == nullptr)
	{
		m_ASInstance = std::make_unique<GameAudioSystem>(); 
	}
	else
	{
		m_ASInstance = std::move(ASInstance);
	}
}