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
#include "Renderer.h"

//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "CameraComponent.h"
#include "TimerComponent.h"

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

//Sound
#include "AudioServiceLocator.h"
#include "AudioLogSystem.h"
#include "GameAudioSystem.h"

#include <iostream>

void load()
{
	dae::AudioServiceLocator::RegisterSoundSystem(std::make_unique<dae::AudioLogSystem>(std::make_unique<dae::GameAudioSystem>()));
	auto& resourceManager = dae::ResourceManager::GetInstance();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto bombermanFont = dae::ResourceManager::GetInstance().LoadFont("bombermanFont.otf", 14);

	// --------------------
	// BOMBERMAN MENU SCENE
	// --------------------
	auto& bombermanMenuScene = dae::SceneManager::GetInstance().CreateScene("bombermanMenu");

	auto menuObject = std::make_unique<dae::GameObject>();
	menuObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(menuObject.get()));
	menuObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BombermanTitle.png"));
	menuObject->SetLocalPosition(0, 0);
	bombermanMenuScene.Add(std::move(menuObject));

	// --------------------
	// BOMBERMAN STAGE SCENE
	// --------------------
	auto& bombermanStageScene = dae::SceneManager::GetInstance().CreateScene("bombermanStage");

	auto stageObject = std::make_unique<dae::GameObject>();
	stageObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(stageObject.get()));
	stageObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(stageObject.get()));

	stageObject->GetComponent<dae::TextComponent>()->SetText("STAGE 1");
	stageObject->GetComponent<dae::TextComponent>()->SetFont(bombermanFont); 
	stageObject->SetLocalPosition(200, 230);

	bombermanStageScene.Add(std::move(stageObject));

	// -------------------------
	// BOMBERMAN HIGHSCORE SCENE
	// -------------------------
	auto& bombermanHighscoreScene = dae::SceneManager::GetInstance().CreateScene("bombermanHighscore");

	auto highscoreObject = std::make_unique<dae::GameObject>();
	highscoreObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(highscoreObject.get()));
	highscoreObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("HighscoreBoard.png"));
	highscoreObject->SetLocalPosition(0, 0);
	bombermanHighscoreScene.Add(std::move(highscoreObject));

	auto highscoreTextObject = std::make_unique<dae::GameObject>();
	highscoreTextObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(highscoreTextObject.get()));
	highscoreTextObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(highscoreTextObject.get()));
	highscoreTextObject->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
	highscoreTextObject->SetLocalPosition(10, 10);
	bombermanHighscoreScene.Add(std::move(highscoreTextObject));

	// --------------------
	// BOMBERMAN GAME SCENE
	// --------------------
	auto& bombermanGameScene = dae::SceneManager::GetInstance().CreateScene("bombermanGame");
	//bool hasPressedBombButton{ false };

	//BACKGROUND
	auto gameObject = std::make_unique<dae::GameObject>();
	gameObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(gameObject.get(), 2.f));
	gameObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Background.png"));
	gameObject->SetLocalPosition(0, 65);
	bombermanGameScene.Add(std::move(gameObject));

	//TIMER OBJECT
	auto timerObject = std::make_unique<dae::GameObject>();
	timerObject->SetLocalPosition(20, 25);
	timerObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(timerObject.get()));
	timerObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(timerObject.get()));
	timerObject->AddComponent<dae::TimerComponent>(std::make_unique<dae::TimerComponent>(timerObject.get()));

	timerObject->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);   
	timerObject->GetComponent<dae::TimerComponent>()->SetTimeLimit(200.f);
	bombermanGameScene.Add(std::move(timerObject));

	// LIVES & SCORE BOMBERMAN DISPLAY
	auto scoreObjectBomberman = std::make_unique<dae::GameObject>();
	scoreObjectBomberman->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(scoreObjectBomberman.get()));
	scoreObjectBomberman->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(scoreObjectBomberman.get()));
	scoreObjectBomberman->AddComponent<dae::ScoreDisplay>(std::make_unique<dae::ScoreDisplay>(scoreObjectBomberman.get()));
	scoreObjectBomberman->GetComponent<dae::TextComponent>()->SetFont(bombermanFont); 
	scoreObjectBomberman->SetLocalPosition(300, 25);

	auto livesObjectBomberman = std::make_unique<dae::GameObject>();
	livesObjectBomberman->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(livesObjectBomberman.get()));
	livesObjectBomberman->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(livesObjectBomberman.get()));
	livesObjectBomberman->AddComponent<dae::HealthDisplay>(std::make_unique<dae::HealthDisplay>(livesObjectBomberman.get()));
	livesObjectBomberman->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
	livesObjectBomberman->SetLocalPosition(400, 25);

	//BOMBERMAN 
	auto bombermanObject = std::make_unique<dae::GameObject>("Player");
	bombermanObject->SetLocalPosition(70, 300);
	bombermanObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombermanObject.get()));
	bombermanObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(bombermanObject.get()));
	bombermanObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(bombermanObject.get()));

	bombermanObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
	bombermanObject->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectBomberman->GetComponent<dae::HealthDisplay>());
	bombermanObject->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObjectBomberman->GetComponent<dae::ScoreDisplay>());

	bombermanGameScene.Add(std::move(scoreObjectBomberman));
	bombermanGameScene.Add(std::move(livesObjectBomberman));

	//ENEMY
	auto enemyObject = std::make_unique<dae::GameObject>();
	enemyObject->SetLocalPosition(30, 300);

	enemyObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(enemyObject.get()));
	enemyObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(enemyObject.get()));
	enemyObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(enemyObject.get()));

	enemyObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemy.png"));

	//BOMB
	auto bombObject = std::make_unique<dae::GameObject>();
	bombObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombObject.get()));
	bombObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomb.png"));

	//BRICK
	auto brickObject = std::make_unique<dae::GameObject>();
	brickObject->SetLocalPosition((2 * 16) * 2, ((3 * 16) * 2) + 65);
	brickObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(brickObject.get(), 2.f));
	brickObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Brick.png"));
	bombermanGameScene.Add(std::move(brickObject));

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
		enemyObject.get(), glm::vec3{0, -1, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveDownCommandBM{ std::make_unique<dae::MovementCommand>(
		enemyObject.get(), glm::vec3{0, 1, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveLeftCommandBM{ std::make_unique<dae::MovementCommand>(
		enemyObject.get(), glm::vec3{-1, 0, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveRightCommandBM{ std::make_unique<dae::MovementCommand>(
		enemyObject.get(), glm::vec3{1, 0, 0}, 100.f) };

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
		dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(enemyObject.get()));

	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::A,
		dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(enemyObject.get(), scoreIncrementBy10));
	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::B,
		dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(enemyObject.get(), scoreIncrementBy100));

	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::Y,
		dae::ButtonState::Is_Pressed, std::make_unique<dae::BombCommand>(bombObject.get()));

	// KEYBOARD
	// --------
	std::unique_ptr<dae::MovementCommand> moveUpCommandE{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{0, -1, 0}, 150.f) };
	std::unique_ptr<dae::MovementCommand> moveDownCommandE{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{0, 1, 0}, 150.f) };
	std::unique_ptr<dae::MovementCommand> moveLeftCommandE{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{-1, 0, 0}, 150.f) };
	std::unique_ptr<dae::MovementCommand> moveRightCommandE{ std::make_unique<dae::MovementCommand>(
		bombermanObject.get(), glm::vec3{1, 0, 0}, 150.f) };

	input.AddKeyboardCommand(SDL_SCANCODE_W, dae::ButtonState::Is_Pressed, std::move(moveUpCommandE));
	input.AddKeyboardCommand(SDL_SCANCODE_S, dae::ButtonState::Is_Pressed, std::move(moveDownCommandE));
	input.AddKeyboardCommand(SDL_SCANCODE_A, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandE));
	input.AddKeyboardCommand(SDL_SCANCODE_D, dae::ButtonState::Is_Pressed, std::move(moveRightCommandE));

	input.AddKeyboardCommand(SDL_SCANCODE_C, dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(bombermanObject.get()));

	input.AddKeyboardCommand(SDL_SCANCODE_Z, dae::ButtonState::Is_Up,
		std::make_unique<dae::ScoreCommand>(bombermanObject.get(), scoreIncrementBy10));
	input.AddKeyboardCommand(SDL_SCANCODE_X, dae::ButtonState::Is_Up,
		std::make_unique<dae::ScoreCommand>(bombermanObject.get(), scoreIncrementBy100));

	bombermanGameScene.Add(std::move(enemyObject));
	bombermanGameScene.Add(std::move(bombermanObject));
}

int main(int, char* []) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}