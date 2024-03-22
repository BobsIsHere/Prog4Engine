#include <string>
#include "GameObject.h"
#include "HealthDisplay.h"
#include "TextComponent.h"
#include "HealthComponent.h"

dae::HealthDisplay::HealthDisplay(GameObject* gameObject) :
	Component{ gameObject }
{
	const auto textComponent = gameObject->GetComponent<TextComponent>();
	textComponent->SetText("# Lives: 3");
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
		break;
	case dae::Event::Event_Enemy_Hit:
		UpdateText(gameObject); 
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
