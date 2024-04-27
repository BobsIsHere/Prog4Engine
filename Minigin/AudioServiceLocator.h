#pragma once
#include <memory>

namespace dae
{
	class AudioSystem;

	class AudioServiceLocator final
	{
	public:
		AudioServiceLocator() = delete;
		~AudioServiceLocator() = delete;

		static AudioSystem& GetAudioSystem();
		static void RegisterSoundSystem(std::unique_ptr<AudioSystem>&& ASInstance);

	private:
		static std::unique_ptr<AudioSystem> m_ASInstance;
	};
}