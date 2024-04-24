#include "NullAudioSystem.h"
#include "ServiceLocator.h"
#include "AudioSystem.h"

dae::AudioSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_ASInstance;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<AudioSystem>&& ASInstance)
{
	m_ASInstance = std::move(ASInstance);
}
