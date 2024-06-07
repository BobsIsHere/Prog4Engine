#include "DetonatorPowerUpDisplay.h"
#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "BombManager.h"
#include "GameObject.h"

dae::DetonatorPowerUpDisplay::DetonatorPowerUpDisplay(GameObject* pGameObject) :
	Component(pGameObject)
{
}

dae::DetonatorPowerUpDisplay::~DetonatorPowerUpDisplay()
{
}

void dae::DetonatorPowerUpDisplay::Notify(GameObject*, Event event)
{
	switch (event)
	{
	case dae::Event::Event_Detonator_PowerUp_PickedUp:
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanPowerUp.wav", 0.5f);
		BombManager::GetInstance().EnableDetonator(true);
		break;
	default:
		break;
	}
}
