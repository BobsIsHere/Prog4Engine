#include <iostream>
#include "AudioLogSystem.h"

dae::AudioLogSystem::AudioLogSystem(std::unique_ptr<AudioSystem> audioSystem) :
	AudioSystem(),
	m_AudioSystem{ std::move(audioSystem) }
{
}

dae::AudioLogSystem::~AudioLogSystem()
{
}

void dae::AudioLogSystem::PlayMusic(std::string filePath, const float volume)
{
	Log("PlayMusic");
	m_AudioSystem->PlayMusic(filePath, volume);
}

void dae::AudioLogSystem::StopMusic()
{
	Log("StopMusic");
	m_AudioSystem->StopMusic();
}

void dae::AudioLogSystem::PlaySoundEffect(std::string filePath, const float volume)
{
	Log("PlaySoundEffect");
	m_AudioSystem->PlaySoundEffect(filePath, volume);
}

void dae::AudioLogSystem::StopAllMusic()
{
	Log("StopAllMusic");
	m_AudioSystem->StopAllMusic();
}

void dae::AudioLogSystem::PauseAudio()
{
	Log("PauseAudio");
	m_AudioSystem->PauseAudio();
}

void dae::AudioLogSystem::ResumeAudio()
{
	Log("ResumeAudio");
	m_AudioSystem->ResumeAudio();
}

void dae::AudioLogSystem::AudioEventHandler()
{
	m_AudioSystem->AudioEventHandler();
}

void dae::AudioLogSystem::Log(const char* message)
{
	std::cout << "LoggedAudio: " << message << std::endl;
}
