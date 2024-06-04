#include "BombDisplay.h"
#include "GameAudioSystem.h"
#include "AudioServiceLocator.h"

dae::BombDisplay::BombDisplay(GameObject* pGameObject) :
	Component( pGameObject )
{
}

dae::BombDisplay::~BombDisplay()
{
}

void dae::BombDisplay::Notify(GameObject*, Event event)
{
	if (event == Event::Event_Bomb_Dropped)
	{
		// Display bomb
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanDropsBomb.wav", 0.5f);
	}
	else if (event == Event::Event_Bomb_Exploded)
	{
		// Remove bomb
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanExplosion.wav", 0.75f);
	}
}
