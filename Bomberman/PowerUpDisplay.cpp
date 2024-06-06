#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "PowerUpDisplay.h"
#include "BombManager.h"
#include "GameObject.h"

dae::PowerUpDisplay::PowerUpDisplay(GameObject* pGameObject) :
	Component(pGameObject)  
{
}

dae::PowerUpDisplay::~PowerUpDisplay()
{
}

void dae::PowerUpDisplay::Notify(GameObject*, Event event)
{
	switch (event)
	{
	case dae::Event::Event_Extra_Bomb_PowerUp_PickedUp:
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanPowerUp.wav", 0.5f);
		BombManager::GetInstance().IncreaseBombLimit(1);
		break;
	case dae::Event::Event_Flame_PowerUp_PickedUp:
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanPowerUp.wav", 0.5f);
		break;
	case dae::Event::Event_Detonator_PowerUp_PickedUp:
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanPowerUp.wav", 0.5f);
		break;
	default:
		break;
	}
}
