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
#include "InputManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "CacheGraphComponent.h"
#include "MovementCommand.h"
#include "Controller.h"

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

	//CONTROLLER CONTROLS TEXT
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	textObject = std::make_shared<dae::GameObject>();
	textObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(textObject.get()));
	textObject->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(textObject.get()));
	textObject->GetComponent<dae::TextComponent>()->SetText("Use the D-Pad to move Bomberman");
	textObject->GetComponent<dae::TextComponent>()->SetFont(font);
	textObject->SetLocalPosition(5, 100);
	scene.Add(textObject);

	//KEYBOARD CONTROLS TEXT
	textObject = std::make_shared<dae::GameObject>();
	textObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(textObject.get()));
	textObject->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(textObject.get()));
	textObject->GetComponent<dae::TextComponent>()->SetText("Use WASD to move the enemy");
	textObject->GetComponent<dae::TextComponent>()->SetFont(font);
	textObject->SetLocalPosition(5, 130);
	scene.Add(textObject);

	//BOMBERMAN
	auto bombermanObject = std::make_shared<dae::GameObject>();
	bombermanObject->SetLocalPosition(70,300);
	bombermanObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(bombermanObject.get()));
	bombermanObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
	scene.Add(bombermanObject); 

	//ENEMY
	auto enemyObject = std::make_shared<dae::GameObject>();
	enemyObject->SetLocalPosition(30, 300);
	enemyObject->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(enemyObject.get()));
	enemyObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemy.png"));
	scene.Add(enemyObject); 

	//CACHE
	/*auto cacheObject = std::make_shared<dae::GameObject>(); 
	cacheObject->AddComponent<dae::CacheGraphComponent>(std::make_shared<dae::CacheGraphComponent>(cacheObject.get()));
	scene.Add(cacheObject); */

	//--------------------
	// SCENE.ADD PLEASE !!!!!!!!
	//--------------------

	//--------------------
	//		INPUT
	//--------------------
	auto& input = dae::InputManager::GetInstance();

	// CONTROLLER
	// ----------
	std::unique_ptr<dae::MovementCommand> moveUpCommandBM{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{0, -1, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveDownCommandBM{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{0, 1, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveLeftCommandBM{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{-1, 0, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveRightCommandBM{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{1, 0, 0}, 100.f) };

	// CONTROLLER 1
	input.AddCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), 
		dae::Controller::GamePad::Dpad_Up, dae::ButtonState::Is_Pressed, std::move(moveUpCommandBM));
	input.AddCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), 
		dae::Controller::GamePad::Dpad_Down, dae::ButtonState::Is_Pressed, std::move(moveDownCommandBM));
	input.AddCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), 
		dae::Controller::GamePad::Dpad_Left, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandBM));
	input.AddCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), 
		dae::Controller::GamePad::Dpad_Right, dae::ButtonState::Is_Pressed, std::move(moveRightCommandBM));

	// KEYBOARD
	// --------
	std::unique_ptr<dae::MovementCommand> moveUpCommandE{ std::make_unique<dae::MovementCommand>(
		enemyObject.get(), glm::vec3{0, -1, 0}, 200.f) };
	std::unique_ptr<dae::MovementCommand> moveDownCommandE{ std::make_unique<dae::MovementCommand>(
		enemyObject.get(), glm::vec3{0, 1, 0}, 200.f) };
	std::unique_ptr<dae::MovementCommand> moveLeftCommandE{ std::make_unique<dae::MovementCommand>(
		enemyObject.get(), glm::vec3{-1, 0, 0}, 200.f) };
	std::unique_ptr<dae::MovementCommand> moveRightCommandE{ std::make_unique<dae::MovementCommand>(
		enemyObject.get(), glm::vec3{1, 0, 0}, 200.f) };

	input.AddCommand(SDL_SCANCODE_W, dae::ButtonState::Is_Pressed, std::move(moveUpCommandE));
	input.AddCommand(SDL_SCANCODE_S, dae::ButtonState::Is_Pressed, std::move(moveDownCommandE));
	input.AddCommand(SDL_SCANCODE_A, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandE));
	input.AddCommand(SDL_SCANCODE_D, dae::ButtonState::Is_Pressed, std::move(moveRightCommandE));
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}