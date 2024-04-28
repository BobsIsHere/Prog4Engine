#include <string>
#include <iostream>

#include "GameObject.h"
#include "HealthDisplay.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "GameAudioSystem.h"
#include "AudioServiceLocator.h"

dae::HealthDisplay::HealthDisplay(GameObject* gameObject) :
	Component{ gameObject }
{
	try
	{
		const auto textComponent = gameObject->GetComponent<TextComponent>();
		textComponent->SetText("# Lives: 3");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

dae::HealthDisplay::~HealthDisplay()
{
}

void dae::HealthDisplay::Notify(GameObject* gameObject, Event event)
{
	switch (event)
	{
	case dae::Event::Event_Player_Hit:
		UpdateText(gameObject);
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanDies.wav", 0.5f);
		break;
	}
}

void dae::HealthDisplay::UpdateText(GameObject* gameObject)
{
	std::string healthText{}; 
	if (gameObject->HasComponent<HealthComponent>())
	{
		const auto healthComponent = gameObject->GetComponent<HealthComponent>();
		healthText = "# Lives: " + std::to_string(healthComponent->GetLives());
	}

	if (GetGameObject()->HasComponent<TextComponent>())
	{
		const auto textComponent = GetGameObject()->GetComponent<TextComponent>();
		textComponent->SetText(healthText); 
	}
}
