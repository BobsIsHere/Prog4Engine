#include "AudioServiceLocator.h"
#include "BombPowerUpDisplay.h"
#include "GameAudioSystem.h"
#include "BombManager.h"
#include "GameObject.h"

dae::BombPowerUpDisplay::BombPowerUpDisplay(GameObject* pGameObject) :
	Component(pGameObject)  
{
}

dae::BombPowerUpDisplay::~BombPowerUpDisplay()
{
}

void dae::BombPowerUpDisplay::Notify(GameObject*, Event event)
{
	switch (event)
	{
	case dae::Event::Event_Extra_Bomb_PowerUp_PickedUp:
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanPowerUp.wav", 0.5f);
		BombManager::GetInstance().IncreaseBombLimit(1);
		break;
	default:
		break;
	}
}
