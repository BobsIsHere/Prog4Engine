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
#include "GameStateUpdater.h"

//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "CameraComponent.h"
#include "TimerComponent.h"
#include "PlayerComponent.h"
#include "BoundingBoxComponent.h"
#include "BombComponent.h"
#include "EnemyCollisionComponent.h"
#include "RoamerBehaviorComponent.h"
#include "ChaserBehaviorComponent.h"

#include "HealthComponent.h"
#include "ScoreComponent.h"

//Commands
#include "MovementCommand.h"
#include "DetonateCommand.h"
#include "HealthCommand.h"
#include "ScoreCommand.h"
#include "BombCommand.h"

//Observers
#include "HealthDisplay.h"
#include "ScoreDisplay.h"
#include "BombPowerUpDisplay.h"
#include "FlamesPowerUpDisplay.h"
#include "DetonatorPowerUpDisplay.h"

//Sound
#include "AudioServiceLocator.h"
#include "AudioLogSystem.h"
#include "GameAudioSystem.h"
#include "NullAudioSystem.h"

#include <iostream>

void load()
{
	dae::AudioServiceLocator::RegisterSoundSystem(std::make_unique<dae::AudioLogSystem>(std::make_unique<dae::NullAudioSystem>())); 
	auto& resourceManager = dae::ResourceManager::GetInstance();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto bombermanFont = dae::ResourceManager::GetInstance().LoadFont("bombermanFont.otf", 14);

	const int uiSize{ 64 };

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

	//BACKGROUND
	auto gameObject = std::make_unique<dae::GameObject>();
	gameObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(gameObject.get(), 2.f));
	gameObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Background.png"));
	gameObject->SetLocalPosition(0, uiSize);
	bombermanGameScene.Add(std::move(gameObject));

	//WALLS
	const float blockWidth{ 32.f };  
	const float blockHeight{ 32.f };  
	const int amountOfRows{ 13 }; 
	const int amountOfColumns{ 16 }; 

	// BORDER BLOCKS
	// Top border
	auto topBorderObject = std::make_unique<dae::GameObject>("Border");
	topBorderObject->SetLocalPosition(0, uiSize);
	topBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
		topBorderObject.get(), blockWidth * amountOfColumns, blockHeight)); 

	bombermanGameScene.Add(std::move(topBorderObject)); 

	// Bottom border
	auto bottomBorderObject = std::make_unique<dae::GameObject>("Border");
	bottomBorderObject->SetLocalPosition(0, 480 - blockHeight);  
	bottomBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>( 
		bottomBorderObject.get(), blockWidth * amountOfColumns, blockHeight));

	bombermanGameScene.Add(std::move(bottomBorderObject)); 
	 
	// Left border
	auto leftBorderObject = std::make_unique<dae::GameObject>("Border");
	leftBorderObject->SetLocalPosition(0, uiSize);
	leftBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>( 
		leftBorderObject.get(), blockWidth, blockHeight * amountOfRows)); 

	bombermanGameScene.Add(std::move(leftBorderObject));

	// Right border
	auto rightBorderObject = std::make_unique<dae::GameObject>("Border");
	rightBorderObject->SetLocalPosition(blockWidth * amountOfColumns, uiSize);
	rightBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
		rightBorderObject.get(), blockWidth, blockHeight * amountOfRows));

	bombermanGameScene.Add(std::move(rightBorderObject));

	// INNER BLOCKS
	for (int rowIdx = 1; rowIdx < amountOfRows; ++rowIdx) 
	{
		if ((rowIdx + 1) % 7 != 0)
		{
			for (int columnIdx = 1; columnIdx < amountOfColumns - 1; ++columnIdx)
			{ 
				auto blockObject = std::make_unique<dae::GameObject>("Border"); 
				blockObject->SetLocalPosition((blockWidth * columnIdx) * 2, ((blockHeight * rowIdx) * 2) + uiSize);
				blockObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>( 
					blockObject.get(), blockWidth, blockHeight)); 
				bombermanGameScene.Add(std::move(blockObject)); 
			}
		}
	}

	//BRICK
	auto brickObject = std::make_unique<dae::GameObject>("Breakable");
	brickObject->SetLocalPosition((2 * 16) * 2, ((3 * 16) * 2) + uiSize);
	brickObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(brickObject.get(), 2.f));
	brickObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(brickObject.get(), 32.f, 32.f));

	brickObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Brick.png"));
	bombermanGameScene.Add(std::move(brickObject));

	//POWER-UP
	auto bombPowerUpObject = std::make_unique<dae::GameObject>("BombPowerUp");
	bombPowerUpObject->SetLocalPosition(7 * 32, 288);
	bombPowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombPowerUpObject.get(), 2.f));
	bombPowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(bombPowerUpObject.get(), 16.f, 16.f));
	bombPowerUpObject->AddComponent<dae::BombPowerUpDisplay>(std::make_unique<dae::BombPowerUpDisplay>(bombPowerUpObject.get()));

	bombPowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("ExtraBombPowerUp.png"));

	auto flamePowerUpObject = std::make_unique<dae::GameObject>("FlamePowerUp");
	flamePowerUpObject->SetLocalPosition(5 * 32, (4 * 32) + 65);
	flamePowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(flamePowerUpObject.get(), 2.f));
	flamePowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(flamePowerUpObject.get(), 16.f, 16.f));
	flamePowerUpObject->AddComponent < dae::FlamesPowerUpDisplay > (std::make_unique<dae::FlamesPowerUpDisplay>(flamePowerUpObject.get()));

	flamePowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("FlamesPowerUp.png"));

	auto detonatorPowerUpObject = std::make_unique<dae::GameObject>("DetonatorPowerUp");
	detonatorPowerUpObject->SetLocalPosition(5 * 32, (8 * 32) + 65);
	detonatorPowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(detonatorPowerUpObject.get(), 2.f));
	detonatorPowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(detonatorPowerUpObject.get(), 16.f, 16.f));
	detonatorPowerUpObject->AddComponent<dae::DetonatorPowerUpDisplay>(std::make_unique<dae::DetonatorPowerUpDisplay>(detonatorPowerUpObject.get()));

	detonatorPowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("DetonatorPowerUp.png"));

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
	bombermanObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(bombermanObject.get(), 3));
	bombermanObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(bombermanObject.get()));
	bombermanObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(bombermanObject.get(), 32.f, 32.f));
	bombermanObject->AddComponent<dae::PlayerComponent>(std::make_unique<dae::PlayerComponent>(bombermanObject.get()));

	bombermanObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
	bombermanObject->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectBomberman->GetComponent<dae::HealthDisplay>());
	bombermanObject->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObjectBomberman->GetComponent<dae::ScoreDisplay>());
	bombermanObject->GetComponent<dae::PlayerComponent>()->AddObserver(bombPowerUpObject->GetComponent<dae::BombPowerUpDisplay>());
	bombermanObject->GetComponent<dae::PlayerComponent>()->AddObserver(flamePowerUpObject->GetComponent<dae::FlamesPowerUpDisplay>());
	bombermanObject->GetComponent<dae::PlayerComponent>()->AddObserver(detonatorPowerUpObject->GetComponent<dae::DetonatorPowerUpDisplay>());

	bombermanGameScene.Add(std::move(scoreObjectBomberman));
	bombermanGameScene.Add(std::move(livesObjectBomberman));
	bombermanGameScene.Add(std::move(bombPowerUpObject));
	bombermanGameScene.Add(std::move(flamePowerUpObject));
	bombermanGameScene.Add(std::move(detonatorPowerUpObject));

	//ENEMY
	auto balloomObject = std::make_unique<dae::GameObject>("Enemy");
	balloomObject->SetLocalPosition(7 * 32, 288);

	balloomObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(balloomObject.get()));
	balloomObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(balloomObject.get()));
	balloomObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(balloomObject.get()));
	balloomObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(balloomObject.get(), 32.f, 32.f));
	balloomObject->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(balloomObject.get()));
	balloomObject->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
					balloomObject.get(), 100.f));

	balloomObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Balloom.png"));

	/*auto onealObject = std::make_unique<dae::GameObject>("Enemy");
	onealObject->SetLocalPosition(5 * 32, (4 * 32) + 65);

	onealObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(onealObject.get(), 2.f));
	onealObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(onealObject.get(), 32.f, 32.f));
	onealObject->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(onealObject.get()));
	onealObject->AddComponent<dae::ChaserBehaviorComponent>(std::make_unique<dae::ChaserBehaviorComponent>(onealObject.get(), 130.f, bombermanObject.get()));

	onealObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Oneal.png"));
	bombermanGameScene.Add(std::move(onealObject));*/

	//DOOR

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
		balloomObject.get(), glm::vec3{0, -1, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveDownCommandBM{ std::make_unique<dae::MovementCommand>(
		balloomObject.get(), glm::vec3{0, 1, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveLeftCommandBM{ std::make_unique<dae::MovementCommand>(
		balloomObject.get(), glm::vec3{-1, 0, 0}, 100.f) };
	std::unique_ptr<dae::MovementCommand> moveRightCommandBM{ std::make_unique<dae::MovementCommand>(
		balloomObject.get(), glm::vec3{1, 0, 0}, 100.f) };

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
		dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(balloomObject.get()));

	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::A,
		dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(balloomObject.get(), scoreIncrementBy10));
	input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::B,
		dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(balloomObject.get(), scoreIncrementBy100));

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

	input.AddKeyboardCommand(SDL_SCANCODE_SPACE, dae::ButtonState::Is_Up, std::make_unique<dae::BombCommand>(bombermanObject.get()));
	input.AddKeyboardCommand(SDL_SCANCODE_B, dae::ButtonState::Is_Up, std::make_unique<dae::DetonateCommand>(bombermanObject.get()));

	bombermanGameScene.Add(std::move(balloomObject));
	bombermanGameScene.Add(std::move(bombermanObject));
}

int main(int, char* []) 
{
	dae::Minigin engine("../Data/");
	std::unique_ptr<dae::GameStateUpdater> gameStateUpdater{ std::make_unique<dae::GameStateUpdater>() };
	engine.Run(load, gameStateUpdater.get());
	return 0;
}