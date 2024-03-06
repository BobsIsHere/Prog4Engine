#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"

#include "../3rdParty/imgui-1.90.4/imgui.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& resourceManager = dae::ResourceManager::GetInstance();

	//BACKGROUND
	auto gameObject = std::make_shared<dae::GameObject>();
	gameObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(gameObject.get()));
	gameObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("background.tga"));
	scene.Add(gameObject);

	//BACKGROUND LOGO
	gameObject = std::make_shared<dae::GameObject>();
	gameObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(gameObject.get()));
	gameObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("logo.tga"));
	gameObject->SetLocalPosition(216, 180);
	scene.Add(gameObject);

	//BACKRGOUND TEXT
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textObject = std::make_shared<dae::GameObject>();
	textObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(textObject.get()));
	textObject->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(textObject.get()));
	textObject->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	textObject->GetComponent<dae::TextComponent>()->SetFont(font); 
	textObject->SetLocalPosition(100,30);
	scene.Add(textObject);

	//FPS COUNTER
	textObject = std::make_shared<dae::GameObject>(); 
	textObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(textObject.get()));
	textObject->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(textObject.get()));
	textObject->GetComponent<dae::TextComponent>()->SetFont(font);
	textObject->AddComponent<dae::FPSComponent>(std::make_shared<dae::FPSComponent>(textObject.get()));
	scene.Add(textObject);

	//PIVOT POINT
	auto pivotPointObject = std::make_shared<dae::GameObject>(); 
	pivotPointObject->SetLocalPosition(310, 300);
	scene.Add(pivotPointObject);

	//BOMBERMAN
	auto bombermanObject = std::make_shared<dae::GameObject>();
	bombermanObject->SetLocalPosition(50,0);
	bombermanObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(bombermanObject.get()));
	bombermanObject->AddComponent<dae::RotationComponent>(std::make_shared<dae::RotationComponent>(bombermanObject.get()));
	bombermanObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
	bombermanObject->GetComponent<dae::RotationComponent>()->SetRotationSpeed(250.f);
	bombermanObject->SetParent(pivotPointObject.get(), false);
	scene.Add(bombermanObject); 

	//ENEMY
	auto enemyObject = std::make_shared<dae::GameObject>();
	enemyObject->SetLocalPosition(30, 0);
	enemyObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(enemyObject.get()));
	enemyObject->AddComponent<dae::RotationComponent>(std::make_shared<dae::RotationComponent>(enemyObject.get()));
	enemyObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemy.png"));
	enemyObject->GetComponent<dae::RotationComponent>()->SetRotationSpeed(-300.f);
	enemyObject->SetParent(bombermanObject.get(), false);
	scene.Add(enemyObject); 
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}