#include <string>
#include <iostream>

#include "GameObject.h"
#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include "GameAudioSystem.h"
#include "AudioServiceLocator.h"

dae::ScoreDisplay::ScoreDisplay(GameObject* gameObject) :
	Component{ gameObject }
{
	try
	{
		const auto textComponent = gameObject->GetComponent<TextComponent>();
		textComponent->SetText("# Score: 0");
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << std::endl; 
	}
}

dae::ScoreDisplay::~ScoreDisplay() 
{
}

void dae::ScoreDisplay::Notify(GameObject* gameObject, Event event)
{
	switch (event)
	{
	case dae::Event::Event_Score_Changed:
		UpdateText(gameObject);
		dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanPowerUp.wav", 0.5f);
		break;
	}
}

void dae::ScoreDisplay::UpdateText(GameObject* gameObject)
{
	std::string scoreText{};
	if (gameObject->HasComponent<ScoreComponent>()) 
	{
		const auto scoreComponent = gameObject->GetComponent<ScoreComponent>(); 
		scoreText = "# Score: " + std::to_string(scoreComponent->GetScore());
	}

	if (GetGameObject()->HasComponent<TextComponent>()) 
	{
		const auto textComponent = GetGameObject()->GetComponent<TextComponent>();
		textComponent->SetText(scoreText);
	}
}