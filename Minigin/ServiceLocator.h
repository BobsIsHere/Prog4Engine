#pragma once
#include <memory>

namespace dae
{
	class AudioSystem;

	class ServiceLocator final
	{
	public:
		ServiceLocator() = delete;
		~ServiceLocator() = delete;

		static AudioSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<AudioSystem>&& ASInstance);

	private:
		static std::unique_ptr<AudioSystem> m_ASInstance;
	};
}