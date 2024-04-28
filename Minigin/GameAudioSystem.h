#pragma once
#include <memory>
#include "AudioSystem.h"

namespace dae
{
	class GameAudioSystem final : public AudioSystem
	{
	public:
		explicit GameAudioSystem();
		virtual ~GameAudioSystem();

		GameAudioSystem(const GameAudioSystem& other) = delete;
		GameAudioSystem(GameAudioSystem&& other) = delete;
		GameAudioSystem& operator=(const GameAudioSystem& other) = delete;
		GameAudioSystem& operator=(GameAudioSystem&& other) = delete; 

		virtual void PlayMusic(std::string filePath, const float volume) override;
		virtual void StopMusic() override;
		virtual void PlaySoundEffect(std::string filePath, const float volume) override;
		virtual void StopAllMusic() override;
		virtual void PauseAudio() override;
		virtual void ResumeAudio() override;
		virtual void AudioEventHandler() override;

	private:
		class SDLAudioSystemImpl;
		std::unique_ptr<SDLAudioSystemImpl> m_pSDLAudioSystemImpl;
	};
}


