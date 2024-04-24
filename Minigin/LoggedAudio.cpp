#include <iostream>
#include "LoggedAudio.h"

dae::LoggedAudio::LoggedAudio(AudioSystem& wrapped) :
	m_Wrapped{ wrapped }
{
}

dae::LoggedAudio::~LoggedAudio()
{
}

void dae::LoggedAudio::PlayMusic(std::string soundID, const float volume)
{
	Log("PlayMusic");
	m_Wrapped.PlayMusic(soundID, volume);
}

void dae::LoggedAudio::StopMusic()
{
	Log("StopMusic");
	m_Wrapped.StopMusic();
}

void dae::LoggedAudio::PlaySoundEffect(std::string soundID, const float volume)
{
	Log("PlaySoundEffect");
	m_Wrapped.PlaySoundEffect(soundID, volume);
}

void dae::LoggedAudio::StopAllMusic()
{
	Log("StopAllMusic");
	m_Wrapped.StopAllMusic();
}

void dae::LoggedAudio::Log(const char* message)
{
	std::cout << "LoggedAudio: " << message << std::endl;
}
