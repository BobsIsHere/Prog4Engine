#pragma once
#include "AudioSystem.h"

namespace dae
{
	class NullAudioSystem final : public AudioSystem
	{
	public:
		virtual ~NullAudioSystem() {};
		virtual void PlayMusic(std::string, const float) override {};
		virtual void StopMusic() override {};
		virtual void PlaySoundEffect(std::string, const float) override {};
		virtual void StopAllMusic() override {}; 
		virtual void AudioEventHandler() override {};
	};
}