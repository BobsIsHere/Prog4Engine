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
	auto bombObject = std::make_unique<GameObject>();
	bombObject->AddComponent<BombComponent>(std::make_unique<BombComponent>(bombObject.get()));
	bombObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(bombObject.get(), 2.f));

	bombObject->GetComponent<TextureComponent>()->SetTexture("Bomb.png");
	bombObject->SetParent(GetGameActor(), false);
	bombObject->SetLocalPosition(GetGameActor()->GetWorldPosition());      
	bombObject->GetComponent<BombComponent>()->StartBombTimer();

	std::cout << "Bomb placed at: " << bombObject->GetWorldPosition().x << ", " << bombObject->GetWorldPosition().y << std::endl; 

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(bombObject));
}
