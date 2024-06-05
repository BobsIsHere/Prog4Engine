#include "TextureComponent.h"
#include "BombComponent.h"
#include "SceneManager.h"
#include "BombCommand.h"
#include "BombDisplay.h"
#include "GameObject.h"
#include "Scene.h"
#include <iostream>

dae::BombCommand::BombCommand(GameObject* actor) :
	GameActorCommand{ actor }
{
}

dae::BombCommand::~BombCommand()
{
}

void dae::BombCommand::Execute()
{
	const int gridsize{ 32 };

	auto bombermanPosition{ GetGameActor()->GetLocalPosition() };

	float bombX{ std::round(bombermanPosition.x / gridsize) * gridsize };
	float bombY{ std::round(bombermanPosition.y / gridsize) * gridsize };

	auto bombObject = std::make_unique<GameObject>();
	bombObject->SetLocalPosition(glm::vec3{ bombX, bombY, 0 });
	bombObject->AddComponent<BombComponent>(std::make_unique<BombComponent>(bombObject.get()));
	bombObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(bombObject.get(), 2.f));

	bombObject->GetComponent<TextureComponent>()->SetTexture("Bomb.png");
	bombObject->SetParent(GetGameActor(), false);    
	bombObject->GetComponent<BombComponent>()->StartBombTimer();

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(bombObject));
}
