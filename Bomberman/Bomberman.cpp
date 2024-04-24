#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <SDL.h>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Controller.h"

//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"

#include "HealthComponent.h"
#include "ScoreComponent.h"

//Commands
#include "MovementCommand.h"
#include "HealthCommand.h"
#include "ScoreCommand.h"
#include "BombCommand.h"

//Observers
#include "HealthDisplay.h"
#include "ScoreDisplay.h"

#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& resourceManager = dae::ResourceManager::GetInstance();
	//bool hasPressedBombButton{ false };

	//BACKGROUND
	auto gameObject = std::make_unique<dae::GameObject>();
	gameObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(gameObject.get()));
	gameObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Background.png"));
	scene.Add(std::move(gameObject));

	//BACKGROUND LOGO
	gameObject = std::make_unique<dae::GameObject>();
	gameObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(gameObject.get()));
	gameObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("logo.tga"));
	gameObject->SetLocalPosition(216, 180);
	scene.Add(std::move(gameObject));

	//BACKRGOUND TEXT
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textObject = std::make_unique<dae::GameObject>();
	textObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(textObject.get()));
	textObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(textObject.get()));
	textObject->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	textObject->GetComponent<dae::TextComponent>()->SetFont(font);
	textObject->SetLocalPosition(100, 30);
	scene.Add(std::move(textObject));

	//FPS COUNTER
	auto fpsObject = std::make_unique<dae::GameObject>();
	fpsObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(fpsObject.get()));
	fpsObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(fpsObject.get()));
	fpsObject->GetComponent<dae::TextComponent>()->SetFont(font);
	fpsObject->AddComponent<dae::FPSComponent>(std::make_unique<dae::FPSComponent>(fpsObject.get()));
	scene.Add(std::move(fpsObject));

	//CONTROLLER CONTROLS TEXT
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	textObject = std::make_unique<dae::GameObject>();
	textObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(textObject.get()));
	textObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(textObject.get()));
	textObject->GetComponent<dae::TextComponent>()->SetText("Use the D-Pad to move Bomberman, X to inflict damage, A and B to increase score");
	textObject->GetComponent<dae::TextComponent>()->SetFont(font);
	textObject->SetLocalPosition(5, 100);
	scene.Add(std::move(textObject));

	//KEYBOARD CONTROLS TEXT
	textObject = std::make_unique<dae::GameObject>();
	textObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(textObject.get()));
	textObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(textObject.get()));
	textObject->GetComponent<dae::TextComponent>()->SetText("Use WASD to move the enemy, C to inflict damage, Z and X to increase score");
	textObject->GetComponent<dae::TextComponent>()->SetFont(font);
	textObject->SetLocalPosition(5, 130);
	scene.Add(std::move(textObject));

	// LIVES & SCORE BOMBERMAN DISPLAY
	auto livesObjectBomberman = std::make_unique<dae::GameObject>();
	livesObjectBomberman->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(livesObjectBomberman.get()));
	livesObjectBomberman->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(livesObjectBomberman.get()));
	livesObjectBomberman->AddComponent<dae::HealthDisplay>(std::make_unique<dae::HealthDisplay>(livesObjectBomberman.get()));
	livesObjectBomberman->GetComponent<dae::TextComponent>()->SetFont(font);
	livesObjectBomberman->SetLocalPosition(5, 160);

	auto scoreObjectBomberman = std::make_unique<dae::GameObject>();
	scoreObjectBomberman->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(scoreObjectBomberman.get()));
	scoreObjectBomberman->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(scoreObjectBomberman.get()));
	scoreObjectBomberman->AddComponent<dae::ScoreDisplay>(std::make_unique<dae::ScoreDisplay>(scoreObjectBomberman.get()));
	scoreObjectBomberman->GetComponent<dae::TextComponent>()->SetFont(font);
	scoreObjectBomberman->SetLocalPosition(5, 180);

	// LIVES & SCORE ENEMY DISPLAY
	auto livesObjectEnemy = std::make_unique<dae::GameObject>();
	livesObjectEnemy->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(livesObjectEnemy.get()));
	livesObjectEnemy->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(livesObjectEnemy.get()));
	livesObjectEnemy->AddComponent<dae::HealthDisplay>(std::make_unique<dae::HealthDisplay>(livesObjectEnemy.get()));
	livesObjectEnemy->GetComponent<dae::TextComponent>()->SetFont(font);
	livesObjectEnemy->SetLocalPosition(5, 200);

	auto scoreObjectEnemy = std::make_unique<dae::GameObject>();
	scoreObjectEnemy->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(scoreObjectEnemy.get()));
	scoreObjectEnemy->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(scoreObjectEnemy.get()));
	scoreObjectEnemy->AddComponent<dae::ScoreDisplay>(std::make_unique<dae::ScoreDisplay>(scoreObjectEnemy.get()));
	scoreObjectEnemy->GetComponent<dae::TextComponent>()->SetFont(font);
	scoreObjectEnemy->SetLocalPosition(5, 220);

	//BOMBERMAN 
	auto bombermanObject = std::make_unique<dae::GameObject>();
	bombermanObject->SetLocalPosition(70, 300);
	bombermanObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombermanObject.get()));
	bombermanObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(bombermanObject.get()));
	bombermanObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(bombermanObject.get()));

	bombermanObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
	bombermanObject->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectBomberman->GetComponent<dae::HealthDisplay>().get());
	bombermanObject->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObjectBomberman->GetComponent<dae::ScoreDisplay>().get());

	scene.Add(std::move(scoreObjectBomberman));
	scene.Add(std::move(livesObjectBomberman));

	//ENEMY
	auto enemyObject = std::make_unique<dae::GameObject>();
	enemyObject->SetLocalPosition(30, 300);
	enemyObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(enemyObject.get()));
	enemyObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(enemyObject.get()));
	enemyObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(enemyObject.get()));

	enemyObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemy.png"));
	enemyObject->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectEnemy->GetComponent<dae::HealthDisplay>().get());
	enemyObject->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObjectEnemy->GetComponent<dae::ScoreDisplay>().get());

	scene.Add(std::move(scoreObjectEnemy));
	scene.Add(std::move(livesObjectEnemy));

	//BOMB
	auto bombObject = std::make_unique<dae::GameObject>();
	bombObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombObject.get()));
	bombObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomb.png"));

	//--------------------
	// SCENE.ADD PLEASE !!!!!!!!
	//--------------------

	//--------------------
	//		INPUT
	//--------------------
	auto& input = dae::InputManager::GetInstance();

	const int scoreIncrementBy10{ 10 };
	const int scoreIncrementBy100{ 100 };

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
	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
		dae::Controller::GamePad::Dpad_Up, dae::ButtonState::Is_Pressed, std::move(moveUpCommandBM));
	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
		dae::Controller::GamePad::Dpad_Down, dae::ButtonState::Is_Pressed, std::move(moveDownCommandBM));
	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
		dae::Controller::GamePad::Dpad_Left, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandBM));
	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
		dae::Controller::GamePad::Dpad_Right, dae::ButtonState::Is_Pressed, std::move(moveRightCommandBM));

	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::X,
		dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(bombermanObject.get()));

	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::A,
		dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(bombermanObject.get(), scoreIncrementBy10));
	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::B,
		dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(bombermanObject.get(), scoreIncrementBy100));

	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::Y,
		dae::ButtonState::Is_Pressed, std::make_unique<dae::BombCommand>(bombObject.get()));

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

	input.AddKeyboardCommand(SDL_SCANCODE_W, dae::ButtonState::Is_Pressed, std::move(moveUpCommandE));
	input.AddKeyboardCommand(SDL_SCANCODE_S, dae::ButtonState::Is_Pressed, std::move(moveDownCommandE));
	input.AddKeyboardCommand(SDL_SCANCODE_A, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandE));
	input.AddKeyboardCommand(SDL_SCANCODE_D, dae::ButtonState::Is_Pressed, std::move(moveRightCommandE));

	input.AddKeyboardCommand(SDL_SCANCODE_C, dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(enemyObject.get()));

	input.AddKeyboardCommand(SDL_SCANCODE_Z, dae::ButtonState::Is_Up,
		std::make_unique<dae::ScoreCommand>(enemyObject.get(), scoreIncrementBy10));
	input.AddKeyboardCommand(SDL_SCANCODE_X, dae::ButtonState::Is_Up,
		std::make_unique<dae::ScoreCommand>(enemyObject.get(), scoreIncrementBy100));

	scene.Add(std::move(enemyObject));
	scene.Add(std::move(bombermanObject));
}

int main(int, char* []) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}