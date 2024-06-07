#include "FlamesPowerUpDisplay.h"
#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "BombManager.h"
#include "GameObject.h"

dae::FlamesPowerUpDisplay::FlamesPowerUpDisplay(GameObject* pGameObject) :
	Component(pGameObject)
{
}

dae::FlamesPowerUpDisplay::~FlamesPowerUpDisplay()
{
}

void dae::FlamesPowerUpDisplay::Notify(GameObject*, Event event)
{
	switch (event)
	{
	case dae::Event::Event_Flame_PowerUp_PickedUp:
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanPowerUp.wav", 0.5f);
		BombManager::GetInstance().IncreaseExplosionRange(1);
		break;
	default:
		break;
	}
}
