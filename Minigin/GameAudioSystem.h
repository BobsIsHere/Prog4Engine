#pragma once
#include <memory>
#include "AudioSystem.h"

namespace dae
{
	class GameAudioSystem final : public AudioSystem
	{
	public:
		GameAudioSystem();
		virtual ~GameAudioSystem() = default;

		virtual void PlayMusic(std::string soundID, const float volume) override;
		virtual void StopMusic() override;
		virtual void PlaySoundEffect(std::string soundID, const float volume) override;
		virtual void StopAllMusic() override;
		virtual void Update() override;

	private :
		class SDLAudioSystemImpl;
		std::unique_ptr<SDLAudioSystemImpl> m_pSDLAudioSystemImpl;
	};
}


