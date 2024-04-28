#pragma once
#include <memory>
#include "AudioSystem.h"

namespace dae
{
	class AudioLogSystem final : public AudioSystem
	{
	public:
		AudioLogSystem(std::unique_ptr<AudioSystem> audioSystem);
		virtual ~AudioLogSystem();

		virtual void PlayMusic(std::string filePath, const float volume);
		virtual void StopMusic();
		virtual void PlaySoundEffect(std::string filePath, const float volume);
		virtual void StopAllMusic();
		virtual void PauseAudio();
		virtual void ResumeAudio();
		virtual void AudioEventHandler();

	private:
		void Log(const char* message);

		std::unique_ptr<AudioSystem> m_AudioSystem;
	};
}