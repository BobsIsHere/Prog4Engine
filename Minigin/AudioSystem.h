#pragma once
#include <string>
#include <memory>

namespace dae
{
	class AudioSystem
	{
	public:
		virtual ~AudioSystem() = default;
		virtual void PlayMusic(std::string soundID, const float volume) = 0;
		virtual void StopMusic() = 0;
		virtual void PlaySoundEffect(std::string soundID, const float volume) = 0;
		virtual void StopAllMusic() = 0;
		virtual void Update() = 0;
	};
}