#include <map>
#include <SDL.h>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>

#include "GameAudioSystem.h"
#include "SDL_mixer.h"

namespace dae
{
	class GameAudioSystem::SDLAudioSystemImpl final
	{
	public:
		SDLAudioSystemImpl();
		~SDLAudioSystemImpl();

		void PlayMusic(std::string filePath, const float volume);
		void StopMusic();
		void PlaySoundEffect(std::string filePath, const float volume);
		void StopAllMusic();
		void AudioEventHandler();

		struct AudioEvent
		{
			std::string filePath;
			std::string soundID;
			float volume;
		};

	private:
		std::mutex m_SoundEffectMutex;
		std::map<std::string, Mix_Chunk*> m_pSoundEffect{};

		std::mutex m_MusicMutex;
		Mix_Music* m_pMusicToPlay{};

		std::mutex m_AudioEventQueueMutex;
		std::queue<AudioEvent> m_AudioEventQueue;
	};

	GameAudioSystem::GameAudioSystem() :
		m_pSDLAudioSystemImpl{ std::make_unique<SDLAudioSystemImpl>() }
	{
		if (Mix_Init(SDL_INIT_AUDIO) < 0)
		{
			std::cerr << "Error initializing SDL_mixer" << SDL_GetError() << std::endl;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
		{
			std::cerr << "Error open audio SDL_mixer" << Mix_GetError() << std::endl;
		}
	}

	GameAudioSystem::~GameAudioSystem()
	{
	}

	//GAME AUDIO SYSTEM CLASS
	void dae::GameAudioSystem::PlayMusic(std::string filePath, const float volume)
	{
		m_pSDLAudioSystemImpl->PlayMusic(filePath, volume);
	}

	void dae::GameAudioSystem::StopMusic()
	{
		m_pSDLAudioSystemImpl->StopMusic();
	}

	void dae::GameAudioSystem::PlaySoundEffect(std::string filePath, const float volume)
	{
		m_pSDLAudioSystemImpl->PlaySoundEffect(filePath, volume);
	}

	void dae::GameAudioSystem::StopAllMusic()
	{
		m_pSDLAudioSystemImpl->StopAllMusic();
	}

	void GameAudioSystem::AudioEventHandler()
	{
		m_pSDLAudioSystemImpl->AudioEventHandler();
	}

	//SDL AUDIO SYSTEM IMPL CLASS
	GameAudioSystem::SDLAudioSystemImpl::SDLAudioSystemImpl()
	{
	}

	GameAudioSystem::SDLAudioSystemImpl::~SDLAudioSystemImpl()
	{
		for (auto& soundEffect : m_pSoundEffect)
		{
			Mix_FreeChunk(soundEffect.second);
		}

		Mix_FreeMusic(m_pMusicToPlay);
		Mix_CloseAudio();
		Mix_Quit();
	}

	void GameAudioSystem::SDLAudioSystemImpl::PlayMusic(std::string filePath, const float volume)
	{
		AudioEvent event{};
		event.soundID = "Music";
		event.filePath = filePath;
		event.volume = volume;

		std::lock_guard<std::mutex> lock{ m_AudioEventQueueMutex };
		m_AudioEventQueue.push(event);
	}

	void GameAudioSystem::SDLAudioSystemImpl::StopMusic()
	{
		Mix_HaltMusic();
	}

	void GameAudioSystem::SDLAudioSystemImpl::PlaySoundEffect(std::string filePath, const float volume)
	{
		AudioEvent event{};
		event.soundID = "SoundEffect";
		event.filePath = filePath;
		event.volume = volume;

		std::lock_guard<std::mutex> lock{ m_AudioEventQueueMutex };
		m_AudioEventQueue.push(event);
	}

	void GameAudioSystem::SDLAudioSystemImpl::StopAllMusic()
	{
		Mix_HaltChannel(-1);
	}

	void GameAudioSystem::SDLAudioSystemImpl::AudioEventHandler()
	{		
		while (!m_AudioEventQueue.empty())
		{
			AudioEvent event{};
			{
				std::lock_guard<std::mutex> lock{ m_AudioEventQueueMutex }; 
				event = m_AudioEventQueue.front(); 
				m_AudioEventQueue.pop();  
			}

			if (event.soundID == "Music")
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
			else if (event.soundID == "SoundEffect")
			{
				std::lock_guard<std::mutex> lock{ m_SoundEffectMutex }; 
				Mix_Chunk* pSoundEffect{ Mix_LoadWAV(event.filePath.c_str()) };

				if (pSoundEffect != nullptr)
				{
					// Set sound effect volume
					Mix_VolumeChunk(pSoundEffect, static_cast<int>(event.volume * MIX_MAX_VOLUME));

					// Play sound effect
					Mix_PlayChannel(-1, pSoundEffect, 0);

					// Add sound effect to the map
					m_pSoundEffect[event.filePath] = pSoundEffect; 
				}
				else
				{
					std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
				}
			}
		}
	}
}