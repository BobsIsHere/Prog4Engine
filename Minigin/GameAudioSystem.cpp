#include <thread>
#include <mutex>
#include <queue>

#include "GameAudioSystem.h"
#include "SDL_mixer.h"

namespace dae
{
	class GameAudioSystem::SDLAudioSystemImpl final
	{
	public:
		~SDLAudioSystemImpl() = default;

		void PlayMusic(std::string soundID, const float volume);
		void StopMusic();
		void PlaySoundEffect(std::string soundID, const float volume);
		void StopAllMusic();
		void Update();

		struct AudioEvent
		{
			std::string filePath;
			float volume;
		};

	private:
		std::jthread m_AudioThread;

		std::mutex m_SoundEffectMutex;
		Mix_Chunk* m_pSoundEffect{};

		std::mutex m_MusicMutex;
		Mix_Music* m_pMusicToPlay{};

		std::mutex m_AudioEventQueueMutex;
		std::queue<AudioEvent> m_AudioEventQueue;
	};

	GameAudioSystem::GameAudioSystem() :
		m_pSDLAudioSystemImpl{}
	{
		m_pSDLAudioSystemImpl = std::make_unique<SDLAudioSystemImpl>();
	}

	//GAME AUDIO SYSTEM CLASS
	void dae::GameAudioSystem::PlayMusic(std::string soundID, const float volume)
	{
		m_pSDLAudioSystemImpl->PlayMusic(soundID, volume);
	}

	void dae::GameAudioSystem::StopMusic()
	{
		m_pSDLAudioSystemImpl->StopMusic();
	}

	void dae::GameAudioSystem::PlaySoundEffect(std::string soundID, const float volume)
	{
		m_pSDLAudioSystemImpl->PlaySoundEffect(soundID, volume);
	}

	void dae::GameAudioSystem::StopAllMusic()
	{
		m_pSDLAudioSystemImpl->StopAllMusic();
	}

	void dae::GameAudioSystem::Update()
	{
		m_pSDLAudioSystemImpl->Update();
	}

	//SDL AUDIO SYSTEM IMPL CLASS
	void GameAudioSystem::SDLAudioSystemImpl::PlayMusic(std::string soundID, const float volume)
	{
		AudioEvent event{};
		event.filePath = soundID;
		event.volume = volume;

		std::lock_guard<std::mutex> lock{ m_AudioEventQueueMutex };
		m_AudioEventQueue.push(event);
	}

	void GameAudioSystem::SDLAudioSystemImpl::StopMusic()
	{
		Mix_HaltMusic();
	}

	void GameAudioSystem::SDLAudioSystemImpl::PlaySoundEffect(std::string soundID, const float volume)
	{
		AudioEvent event{};
		event.filePath = soundID;
		event.volume = volume;

		std::lock_guard<std::mutex> lock{ m_AudioEventQueueMutex };
		m_AudioEventQueue.push(event);
	}

	void GameAudioSystem::SDLAudioSystemImpl::StopAllMusic()
	{
		Mix_HaltChannel(-1);
	}

	void GameAudioSystem::SDLAudioSystemImpl::Update()
	{
		while (!m_AudioEventQueue.empty())
		{
			AudioEvent event{};
			{
				std::lock_guard<std::mutex> lock{ m_AudioEventQueueMutex }; 
				event = m_AudioEventQueue.front(); 
				m_AudioEventQueue.pop(); 
			}

			if (event.filePath == "Music")
			{
				std::lock_guard<std::mutex> lock{ m_MusicMutex }; 
				m_pMusicToPlay = Mix_LoadMUS(event.filePath.c_str());
				if (m_pMusicToPlay != nullptr) 
				{
					// Set music volume
					Mix_VolumeMusic(static_cast<int>(event.volume * MIX_MAX_VOLUME));

					//Play Music
					Mix_PlayMusic(m_pMusicToPlay, -1);
				}
			}
			else if (event.filePath == "SoundEffect")
			{
				std::lock_guard<std::mutex> lock{ m_SoundEffectMutex }; 
				m_pSoundEffect = Mix_LoadWAV(event.filePath.c_str()); 

				if (m_pSoundEffect != nullptr) 
				{
					// Set sound effect volume
					Mix_VolumeChunk(m_pSoundEffect, static_cast<int>(event.volume * MIX_MAX_VOLUME));

					// Play sound effect
					Mix_PlayChannel(-1, m_pSoundEffect, 0);
				}
			}
		}
	}
}