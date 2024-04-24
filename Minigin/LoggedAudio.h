#pragma once
#include "AudioSystem.h"

namespace dae
{
	class LoggedAudio final : public AudioSystem
	{
	public:
		LoggedAudio(AudioSystem& wrapped);
		virtual ~LoggedAudio();

		virtual void PlayMusic(std::string soundID, const float volume);
		virtual void StopMusic();
		virtual void PlaySoundEffect(std::string soundID, const float volume);
		virtual void StopAllMusic();

	private:
		void Log(const char* message);

		AudioSystem& m_Wrapped;
	};
}