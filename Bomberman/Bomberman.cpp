#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <SDL.h>

#include "Scene.h"
#include "GameObject.h"
#include "Controller.h"
#include "Renderer.h"
#include "GameStateUpdater.h"

//Managers
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "EnemyManager.h"
#include "LevelLoader.h"

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
	// BOMBERMAN GAME SCENE
	// --------------------

	// LEVEL 1
	// -------
	{
		auto& bombermanGameScene = dae::SceneManager::GetInstance().CreateScene("bombermanLevel1");
		auto& enemyManager = dae::EnemyManager::GetInstance();

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

		//BRICKS
		dae::LevelLoader::GetInstance().Initialize("../Data/Level1.txt", bombermanGameScene);
		dae::LevelLoader::GetInstance().LoadLevel();  

		//POWER-UP
		auto bombPowerUpObject = std::make_unique<dae::GameObject>("BombPowerUp");
		bombPowerUpObject->SetLocalPosition(9 * 32, (2 * 32) + uiSize);
		bombPowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombPowerUpObject.get(), 2.f));
		bombPowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(bombPowerUpObject.get(), 16.f, 16.f));
		bombPowerUpObject->AddComponent<dae::BombPowerUpDisplay>(std::make_unique<dae::BombPowerUpDisplay>(bombPowerUpObject.get()));

		bombPowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("ExtraBombPowerUp.png"));

		auto flamePowerUpObject = std::make_unique<dae::GameObject>("FlamePowerUp");
		flamePowerUpObject->SetLocalPosition(10 * 32, (5 * 32) + uiSize);
		flamePowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(flamePowerUpObject.get(), 2.f));
		flamePowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(flamePowerUpObject.get(), 16.f, 16.f));
		flamePowerUpObject->AddComponent < dae::FlamesPowerUpDisplay >(std::make_unique<dae::FlamesPowerUpDisplay>(flamePowerUpObject.get()));

		flamePowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("FlamesPowerUp.png"));

		auto detonatorPowerUpObject = std::make_unique<dae::GameObject>("DetonatorPowerUp");
		detonatorPowerUpObject->SetLocalPosition(9 * 32, (8 * 32) + uiSize);
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

		//ENEMY 2
		auto balloomObject = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(balloomObject.get());
		balloomObject->SetLocalPosition(7 * 32, 288);

		balloomObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(balloomObject.get()));
		balloomObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(balloomObject.get()));
		balloomObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(balloomObject.get()));
		balloomObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(balloomObject.get(), 32.f, 32.f));
		balloomObject->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(balloomObject.get()));
		balloomObject->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
			balloomObject.get(), 60.f));

		balloomObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Balloom.png"));

		//ENEMY 2
		auto balloomObject2 = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(balloomObject2.get());
		balloomObject2->SetLocalPosition(8 * 32, (3 * 32) + uiSize);

		balloomObject2->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(balloomObject2.get(), 32.f, 32.f));
		balloomObject2->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>( 
			balloomObject2.get(), 60.f));

		balloomObject2->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Balloom.png"));

		//ENEMY 3
		auto balloomObject3 = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(balloomObject3.get());
		balloomObject3->SetLocalPosition(12 * 32, (5 * 32) + uiSize);

		balloomObject3->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(balloomObject3.get()));
		balloomObject3->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(balloomObject3.get()));
		balloomObject3->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(balloomObject3.get()));
		balloomObject3->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(balloomObject3.get(), 32.f, 32.f));
		balloomObject3->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(balloomObject3.get()));
		balloomObject3->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
			balloomObject3.get(), 60.f));

		balloomObject3->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Balloom.png"));

		//DOOR
		auto doorObject = std::make_unique<dae::GameObject>("Door");
		doorObject->SetLocalPosition(4 * 32, 288);

		doorObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(doorObject.get(), 2.f));
		doorObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(doorObject.get(), 32.f, 32.f));

		doorObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Door.png"));
		bombermanGameScene.Add(std::move(doorObject));

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
		bombermanGameScene.Add(std::move(balloomObject2));
		bombermanGameScene.Add(std::move(balloomObject3));
		bombermanGameScene.Add(std::move(bombermanObject));
	}

	// LEVEL 2
	// -------
	{
		auto& bombermanGameScene = dae::SceneManager::GetInstance().CreateScene("bombermanLevel2");
		auto& enemyManager = dae::EnemyManager::GetInstance();

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
			topBorderObject.get(), blockWidth* amountOfColumns, blockHeight));

		bombermanGameScene.Add(std::move(topBorderObject));

		// Bottom border
		auto bottomBorderObject = std::make_unique<dae::GameObject>("Border");
		bottomBorderObject->SetLocalPosition(0, 480 - blockHeight);
		bottomBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
			bottomBorderObject.get(), blockWidth* amountOfColumns, blockHeight));

		bombermanGameScene.Add(std::move(bottomBorderObject));

		// Left border
		auto leftBorderObject = std::make_unique<dae::GameObject>("Border");
		leftBorderObject->SetLocalPosition(0, uiSize);
		leftBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
			leftBorderObject.get(), blockWidth, blockHeight* amountOfRows));

		bombermanGameScene.Add(std::move(leftBorderObject));

		// Right border
		auto rightBorderObject = std::make_unique<dae::GameObject>("Border");
		rightBorderObject->SetLocalPosition(blockWidth* amountOfColumns, uiSize);
		rightBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
			rightBorderObject.get(), blockWidth, blockHeight* amountOfRows));

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

		//BRICKS
		dae::LevelLoader::GetInstance().Initialize("../Data/Level2.txt", bombermanGameScene); 
		dae::LevelLoader::GetInstance().LoadLevel(); 

		//POWER-UP
		auto bombPowerUpObject = std::make_unique<dae::GameObject>("BombPowerUp");
		bombPowerUpObject->SetLocalPosition(13 * 32, (6 * 32) + uiSize);
		bombPowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombPowerUpObject.get(), 2.f));
		bombPowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(bombPowerUpObject.get(), 16.f, 16.f));
		bombPowerUpObject->AddComponent<dae::BombPowerUpDisplay>(std::make_unique<dae::BombPowerUpDisplay>(bombPowerUpObject.get()));

		bombPowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("ExtraBombPowerUp.png"));

		auto flamePowerUpObject = std::make_unique<dae::GameObject>("FlamePowerUp");
		flamePowerUpObject->SetLocalPosition(7 * 32, (1 * 32) + uiSize);
		flamePowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(flamePowerUpObject.get(), 2.f));
		flamePowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(flamePowerUpObject.get(), 16.f, 16.f));
		flamePowerUpObject->AddComponent < dae::FlamesPowerUpDisplay >(std::make_unique<dae::FlamesPowerUpDisplay>(flamePowerUpObject.get()));

		flamePowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("FlamesPowerUp.png"));

		auto detonatorPowerUpObject = std::make_unique<dae::GameObject>("DetonatorPowerUp");
		detonatorPowerUpObject->SetLocalPosition(2 * 32, (7 * 32) + uiSize);
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

		// LIVES & SCORE BOMBERMAN PLAYER 1 DISPLAY
		auto scoreObjectPlayer1 = std::make_unique<dae::GameObject>();
		scoreObjectPlayer1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(scoreObjectPlayer1.get()));
		scoreObjectPlayer1->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(scoreObjectPlayer1.get()));
		scoreObjectPlayer1->AddComponent<dae::ScoreDisplay>(std::make_unique<dae::ScoreDisplay>(scoreObjectPlayer1.get()));
		scoreObjectPlayer1->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
		scoreObjectPlayer1->SetLocalPosition(300, 25);

		auto livesObjectPlayer1 = std::make_unique<dae::GameObject>();
		livesObjectPlayer1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(livesObjectPlayer1.get()));
		livesObjectPlayer1->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(livesObjectPlayer1.get()));
		livesObjectPlayer1->AddComponent<dae::HealthDisplay>(std::make_unique<dae::HealthDisplay>(livesObjectPlayer1.get()));
		livesObjectPlayer1->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
		livesObjectPlayer1->SetLocalPosition(400, 25);

		// LIVES & SCORE BOMBERMAN PLAYER 2 DISPLAY
		auto livesObjectPlayer2 = std::make_unique<dae::GameObject>();
		livesObjectPlayer2->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(livesObjectPlayer2.get()));
		livesObjectPlayer2->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(livesObjectPlayer2.get()));
		livesObjectPlayer2->AddComponent<dae::HealthDisplay>(std::make_unique<dae::HealthDisplay>(livesObjectPlayer2.get()));
		livesObjectPlayer2->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
		livesObjectPlayer2->SetLocalPosition(400, 25);

		//BOMBERMAN PLAYER 1
		auto player1 = std::make_unique<dae::GameObject>("Player");
		player1->SetLocalPosition(70, 300);
		player1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(player1.get()));
		player1->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(player1.get(), 3));
		player1->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(player1.get()));
		player1->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(player1.get(), 32.f, 32.f));
		player1->AddComponent<dae::PlayerComponent>(std::make_unique<dae::PlayerComponent>(player1.get()));

		player1->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
		player1->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectPlayer1->GetComponent<dae::HealthDisplay>());
		player1->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObjectPlayer1->GetComponent<dae::ScoreDisplay>());
		player1->GetComponent<dae::PlayerComponent>()->AddObserver(bombPowerUpObject->GetComponent<dae::BombPowerUpDisplay>());
		player1->GetComponent<dae::PlayerComponent>()->AddObserver(flamePowerUpObject->GetComponent<dae::FlamesPowerUpDisplay>());
		player1->GetComponent<dae::PlayerComponent>()->AddObserver(detonatorPowerUpObject->GetComponent<dae::DetonatorPowerUpDisplay>());

		bombermanGameScene.Add(std::move(livesObjectPlayer1));

		//BOMBERMAN PLAYER 2
		auto player2 = std::make_unique<dae::GameObject>("Player2");
		player2->SetLocalPosition(50, 300);
		player2->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(player2.get()));
		player2->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(player2.get(), 3));
		player2->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(player2.get()));
		player2->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(player2.get(), 32.f, 32.f));
		player2->AddComponent<dae::PlayerComponent>(std::make_unique<dae::PlayerComponent>(player2.get()));

		player2->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
		player2->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectPlayer2->GetComponent<dae::HealthDisplay>());
		player2->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObjectPlayer1->GetComponent<dae::ScoreDisplay>());
		player2->GetComponent<dae::PlayerComponent>()->AddObserver(bombPowerUpObject->GetComponent<dae::BombPowerUpDisplay>());
		player2->GetComponent<dae::PlayerComponent>()->AddObserver(flamePowerUpObject->GetComponent<dae::FlamesPowerUpDisplay>());
		player2->GetComponent<dae::PlayerComponent>()->AddObserver(detonatorPowerUpObject->GetComponent<dae::DetonatorPowerUpDisplay>());

		bombermanGameScene.Add(std::move(scoreObjectPlayer1));
		bombermanGameScene.Add(std::move(livesObjectPlayer2));
		bombermanGameScene.Add(std::move(bombPowerUpObject));
		bombermanGameScene.Add(std::move(flamePowerUpObject));
		bombermanGameScene.Add(std::move(detonatorPowerUpObject));

		//ENEMY
		auto balloomObject1 = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(balloomObject1.get());
		balloomObject1->SetLocalPosition(10 * 32, (3 * 32) + uiSize);

		balloomObject1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(balloomObject1.get()));
		balloomObject1->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(balloomObject1.get()));
		balloomObject1->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(balloomObject1.get()));
		balloomObject1->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(balloomObject1.get(), 32.f, 32.f));
		balloomObject1->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(balloomObject1.get()));
		balloomObject1->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
			balloomObject1.get(), 60.f));

		balloomObject1->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Balloom.png"));

		auto balloomObject2 = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(balloomObject2.get());
		balloomObject2->SetLocalPosition(5 * 32, (7 * 32) + uiSize);

		balloomObject2->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(balloomObject2.get(), 32.f, 32.f));
		balloomObject2->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(balloomObject2.get()));
		balloomObject2->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
			balloomObject2.get(), 60.f));

		balloomObject2->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Oneal.png"));

		auto OnealObject1 = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(OnealObject1.get());
		OnealObject1->SetLocalPosition(1 * 32, (5 * 32) + uiSize);

		OnealObject1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(OnealObject1.get()));
		OnealObject1->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(OnealObject1.get()));
		OnealObject1->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(OnealObject1.get()));
		OnealObject1->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(OnealObject1.get(), 32.f, 32.f));
		OnealObject1->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(OnealObject1.get()));
		OnealObject1->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
			OnealObject1.get(), 90.f));

		OnealObject1->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Oneal.png"));

		auto OnealObject2 = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(OnealObject2.get());
		OnealObject2->SetLocalPosition(11 * 32, (9 * 32) + uiSize);

		OnealObject2->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(OnealObject2.get()));
		OnealObject2->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(OnealObject2.get()));
		OnealObject2->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(OnealObject2.get()));
		OnealObject2->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(OnealObject2.get(), 32.f, 32.f));
		OnealObject2->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(OnealObject2.get()));
		OnealObject2->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
			OnealObject2.get(), 90.f));

		OnealObject2->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Oneal.png"));

		//DOOR
		auto doorObject = std::make_unique<dae::GameObject>("Door");
		doorObject->SetLocalPosition(9 * 32, (10 * 32) + uiSize);

		doorObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(doorObject.get(), 2.f));
		doorObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(doorObject.get(), 32.f, 32.f));

		doorObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Door.png"));
		bombermanGameScene.Add(std::move(doorObject));

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
		std::unique_ptr<dae::MovementCommand> moveUpCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{0, -1, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveDownCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{0, 1, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveLeftCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{-1, 0, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveRightCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{1, 0, 0}, 100.f) };

		// CONTROLLER 1
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Up, dae::ButtonState::Is_Pressed, std::move(moveUpCommandP1));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Down, dae::ButtonState::Is_Pressed, std::move(moveDownCommandP1));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Left, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandP1));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Right, dae::ButtonState::Is_Pressed, std::move(moveRightCommandP1));

		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::X,
			dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(player1.get()));

		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::A,
			dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(player1.get(), scoreIncrementBy10)); 
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One), dae::Controller::GamePad::B,
			dae::ButtonState::Is_Up, std::make_unique<dae::ScoreCommand>(player1.get(), scoreIncrementBy100)); 

		// CONTROLLER 2
		std::unique_ptr<dae::MovementCommand> moveUpCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{0, -1, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveDownCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{0, 1, 0}, 100.f) }; 
		std::unique_ptr<dae::MovementCommand> moveLeftCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{-1, 0, 0}, 100.f) }; 
		std::unique_ptr<dae::MovementCommand> moveRightCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{1, 0, 0}, 100.f) }; 

		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Up, dae::ButtonState::Is_Pressed, std::move(moveUpCommandP2));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Down, dae::ButtonState::Is_Pressed, std::move(moveDownCommandP2));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Left, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandP2));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Right, dae::ButtonState::Is_Pressed, std::move(moveRightCommandP2));

		// KEYBOARD
		// --------
		std::unique_ptr<dae::MovementCommand> moveUpCommandE{ std::make_unique<dae::MovementCommand>( 
			player1.get(), glm::vec3{0, -1, 0}, 150.f) };
		std::unique_ptr<dae::MovementCommand> moveDownCommandE{ std::make_unique<dae::MovementCommand>( 
			player1.get(), glm::vec3{0, 1, 0}, 150.f) };
		std::unique_ptr<dae::MovementCommand> moveLeftCommandE{ std::make_unique<dae::MovementCommand>( 
			player1.get(), glm::vec3{-1, 0, 0}, 150.f) };
		std::unique_ptr<dae::MovementCommand> moveRightCommandE{ std::make_unique<dae::MovementCommand>( 
			player1.get(), glm::vec3{1, 0, 0}, 150.f) };

		input.AddKeyboardCommand(SDL_SCANCODE_W, dae::ButtonState::Is_Pressed, std::move(moveUpCommandE));
		input.AddKeyboardCommand(SDL_SCANCODE_S, dae::ButtonState::Is_Pressed, std::move(moveDownCommandE));
		input.AddKeyboardCommand(SDL_SCANCODE_A, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandE));
		input.AddKeyboardCommand(SDL_SCANCODE_D, dae::ButtonState::Is_Pressed, std::move(moveRightCommandE));

		input.AddKeyboardCommand(SDL_SCANCODE_C, dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(player1.get()));

		input.AddKeyboardCommand(SDL_SCANCODE_Z, dae::ButtonState::Is_Up,
			std::make_unique<dae::ScoreCommand>(player1.get(), scoreIncrementBy10));
		input.AddKeyboardCommand(SDL_SCANCODE_X, dae::ButtonState::Is_Up,
			std::make_unique<dae::ScoreCommand>(player1.get(), scoreIncrementBy100));

		input.AddKeyboardCommand(SDL_SCANCODE_SPACE, dae::ButtonState::Is_Up, std::make_unique<dae::BombCommand>(player1.get()));
		input.AddKeyboardCommand(SDL_SCANCODE_B, dae::ButtonState::Is_Up, std::make_unique<dae::DetonateCommand>(player1.get()));

		bombermanGameScene.Add(std::move(balloomObject1)); 
		bombermanGameScene.Add(std::move(balloomObject2)); 
		bombermanGameScene.Add(std::move(OnealObject1)); 
		bombermanGameScene.Add(std::move(OnealObject2)); 
		bombermanGameScene.Add(std::move(player1));
		bombermanGameScene.Add(std::move(player2));
	}

	// LEVEL 3
	// -------
	{
		auto& bombermanGameScene = dae::SceneManager::GetInstance().CreateScene("bombermanLevel3");
		auto& enemyManager = dae::EnemyManager::GetInstance();

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
			topBorderObject.get(), blockWidth* amountOfColumns, blockHeight));

		bombermanGameScene.Add(std::move(topBorderObject));

		// Bottom border
		auto bottomBorderObject = std::make_unique<dae::GameObject>("Border");
		bottomBorderObject->SetLocalPosition(0, 480 - blockHeight);
		bottomBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
			bottomBorderObject.get(), blockWidth* amountOfColumns, blockHeight));

		bombermanGameScene.Add(std::move(bottomBorderObject));

		// Left border
		auto leftBorderObject = std::make_unique<dae::GameObject>("Border");
		leftBorderObject->SetLocalPosition(0, uiSize);
		leftBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
			leftBorderObject.get(), blockWidth, blockHeight* amountOfRows));

		bombermanGameScene.Add(std::move(leftBorderObject));

		// Right border
		auto rightBorderObject = std::make_unique<dae::GameObject>("Border");
		rightBorderObject->SetLocalPosition(blockWidth* amountOfColumns, uiSize);
		rightBorderObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(
			rightBorderObject.get(), blockWidth, blockHeight* amountOfRows));

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

		//BRICKS
		dae::LevelLoader::GetInstance().Initialize("../Data/Level3.txt", bombermanGameScene);
		dae::LevelLoader::GetInstance().LoadLevel(); 

		//POWER-UP
		auto bombPowerUpObject = std::make_unique<dae::GameObject>("BombPowerUp");
		bombPowerUpObject->SetLocalPosition(13 * 32, (9 * 32) + uiSize);
		bombPowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(bombPowerUpObject.get(), 2.f));
		bombPowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(bombPowerUpObject.get(), 16.f, 16.f));
		bombPowerUpObject->AddComponent<dae::BombPowerUpDisplay>(std::make_unique<dae::BombPowerUpDisplay>(bombPowerUpObject.get()));

		bombPowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("ExtraBombPowerUp.png"));

		auto flamePowerUpObject = std::make_unique<dae::GameObject>("FlamePowerUp");
		flamePowerUpObject->SetLocalPosition(7 * 32, (5 * 32) + uiSize);
		flamePowerUpObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(flamePowerUpObject.get(), 2.f));
		flamePowerUpObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(flamePowerUpObject.get(), 16.f, 16.f));
		flamePowerUpObject->AddComponent < dae::FlamesPowerUpDisplay >(std::make_unique<dae::FlamesPowerUpDisplay>(flamePowerUpObject.get()));

		flamePowerUpObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("FlamesPowerUp.png"));

		auto detonatorPowerUpObject = std::make_unique<dae::GameObject>("DetonatorPowerUp");
		detonatorPowerUpObject->SetLocalPosition(4 * 32, (9 * 32) + uiSize);
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

		// LIVES & SCORE BOMBERMAN PLAYER 1 DISPLAY
		auto scoreObjectPlayer1 = std::make_unique<dae::GameObject>();
		scoreObjectPlayer1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(scoreObjectPlayer1.get()));
		scoreObjectPlayer1->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(scoreObjectPlayer1.get()));
		scoreObjectPlayer1->AddComponent<dae::ScoreDisplay>(std::make_unique<dae::ScoreDisplay>(scoreObjectPlayer1.get()));
		scoreObjectPlayer1->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
		scoreObjectPlayer1->SetLocalPosition(300, 25);

		auto livesObjectPlayer1 = std::make_unique<dae::GameObject>();
		livesObjectPlayer1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(livesObjectPlayer1.get()));
		livesObjectPlayer1->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(livesObjectPlayer1.get()));
		livesObjectPlayer1->AddComponent<dae::HealthDisplay>(std::make_unique<dae::HealthDisplay>(livesObjectPlayer1.get()));
		livesObjectPlayer1->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
		livesObjectPlayer1->SetLocalPosition(400, 25);

		// LIVES & SCORE BOMBERMAN PLAYER 2 DISPLAY
		auto livesObjectPlayer2 = std::make_unique<dae::GameObject>();
		livesObjectPlayer2->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(livesObjectPlayer2.get()));
		livesObjectPlayer2->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(livesObjectPlayer2.get()));
		livesObjectPlayer2->AddComponent<dae::HealthDisplay>(std::make_unique<dae::HealthDisplay>(livesObjectPlayer2.get()));
		livesObjectPlayer2->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
		livesObjectPlayer2->SetLocalPosition(400, 25);

		//BOMBERMAN PLAYER 1
		auto player1 = std::make_unique<dae::GameObject>("Player");
		player1->SetLocalPosition(32, 32 + uiSize);
		player1->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(player1.get()));
		player1->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(player1.get(), 3));
		player1->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(player1.get()));
		player1->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(player1.get(), 32.f, 32.f));
		player1->AddComponent<dae::PlayerComponent>(std::make_unique<dae::PlayerComponent>(player1.get()));

		player1->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Bomberman.png"));
		player1->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectPlayer1->GetComponent<dae::HealthDisplay>());
		player1->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObjectPlayer1->GetComponent<dae::ScoreDisplay>());
		player1->GetComponent<dae::PlayerComponent>()->AddObserver(bombPowerUpObject->GetComponent<dae::BombPowerUpDisplay>());
		player1->GetComponent<dae::PlayerComponent>()->AddObserver(flamePowerUpObject->GetComponent<dae::FlamesPowerUpDisplay>());
		player1->GetComponent<dae::PlayerComponent>()->AddObserver(detonatorPowerUpObject->GetComponent<dae::DetonatorPowerUpDisplay>());

		bombermanGameScene.Add(std::move(livesObjectPlayer1));

		//BOMBERMAN PLAYER 2
		auto player2 = std::make_unique<dae::GameObject>("Player2");
		player2->SetLocalPosition(15 * 32, 32 + uiSize);
		player2->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(player2.get()));
		player2->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(player2.get(), 3));
		player2->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(player2.get(), 32.f, 32.f));
		player2->AddComponent<dae::PlayerComponent>(std::make_unique<dae::PlayerComponent>(player2.get()));

		player2->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Balloom.png"));
		player2->GetComponent<dae::HealthComponent>()->AddObserver(livesObjectPlayer2->GetComponent<dae::HealthDisplay>());

		bombermanGameScene.Add(std::move(scoreObjectPlayer1));
		bombermanGameScene.Add(std::move(livesObjectPlayer2));
		bombermanGameScene.Add(std::move(bombPowerUpObject));
		bombermanGameScene.Add(std::move(flamePowerUpObject));
		bombermanGameScene.Add(std::move(detonatorPowerUpObject));

		//ENEMY
		auto balloomObject = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(balloomObject.get());
		balloomObject->SetLocalPosition(5 * 32, (7 * 32) + uiSize);

		balloomObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(balloomObject.get())); 
		balloomObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(balloomObject.get())); 
		balloomObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(balloomObject.get())); 
		balloomObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(balloomObject.get(), 32.f, 32.f)); 
		balloomObject->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(balloomObject.get())); 
		balloomObject->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>( 
			balloomObject.get(), 60.f)); 

		balloomObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Balloom.png")); 

		auto onealObject = std::make_unique<dae::GameObject>("Enemy"); 
		enemyManager.AddEnemy(onealObject.get());
		onealObject->SetLocalPosition(11 * 32, (11 * 32) + uiSize); 

		onealObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(onealObject.get())); 
		onealObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(onealObject.get())); 
		onealObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(onealObject.get())); 
		onealObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(onealObject.get(), 32.f, 32.f)); 
		onealObject->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(onealObject.get())); 
		onealObject->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>( 
			onealObject.get(), 90.f));

		onealObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Oneal.png"));

		auto dollObject = std::make_unique<dae::GameObject>("Enemy");
		enemyManager.AddEnemy(dollObject.get());
		dollObject->SetLocalPosition(1 * 32, (9 * 32) + uiSize);

		dollObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(dollObject.get()));
		dollObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(dollObject.get()));
		dollObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(dollObject.get()));
		dollObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(dollObject.get(), 32.f, 32.f));
		dollObject->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(dollObject.get()));
		dollObject->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>(
			dollObject.get(), 90.f)); 

		dollObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Oneal.png"));

		auto minvoObject = std::make_unique<dae::GameObject>("Enemy"); 
		enemyManager.AddEnemy(minvoObject.get()); 
		minvoObject->SetLocalPosition(7 * 32, (3 * 32) + uiSize);
		 
		minvoObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(minvoObject.get())); 
		minvoObject->AddComponent<dae::ScoreComponent>(std::make_unique<dae::ScoreComponent>(minvoObject.get())); 
		minvoObject->AddComponent<dae::HealthComponent>(std::make_unique<dae::HealthComponent>(minvoObject.get())); 
		minvoObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(minvoObject.get(), 32.f, 32.f)); 
		minvoObject->AddComponent<dae::EnemyCollisionComponent>(std::make_unique<dae::EnemyCollisionComponent>(minvoObject.get())); 
		minvoObject->AddComponent<dae::RoamerBehaviorComponent>(std::make_unique<dae::RoamerBehaviorComponent>( 
			minvoObject.get(), 90.f)); 

		minvoObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Enemies/Oneal.png")); 

		//DOOR
		auto doorObject = std::make_unique<dae::GameObject>("Door");
		doorObject->SetLocalPosition(9 * 32, (8 * 32) + uiSize);

		doorObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(doorObject.get(), 2.f));
		doorObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(doorObject.get(), 32.f, 32.f));

		doorObject->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Door.png"));
		bombermanGameScene.Add(std::move(doorObject));

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
		std::unique_ptr<dae::MovementCommand> moveUpCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{0, -1, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveDownCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{0, 1, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveLeftCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{-1, 0, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveRightCommandP1{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{1, 0, 0}, 100.f) };

		// CONTROLLER 1
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Up, dae::ButtonState::Is_Pressed, std::move(moveUpCommandP1));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Down, dae::ButtonState::Is_Pressed, std::move(moveDownCommandP1));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Left, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandP1));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Right, dae::ButtonState::Is_Pressed, std::move(moveRightCommandP1));

		// CONTROLLER 2
		std::unique_ptr<dae::MovementCommand> moveUpCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{0, -1, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveDownCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{0, 1, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveLeftCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{-1, 0, 0}, 100.f) };
		std::unique_ptr<dae::MovementCommand> moveRightCommandP2{ std::make_unique<dae::MovementCommand>(
			player2.get(), glm::vec3{1, 0, 0}, 100.f) };

		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Up, dae::ButtonState::Is_Pressed, std::move(moveUpCommandP2));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Down, dae::ButtonState::Is_Pressed, std::move(moveDownCommandP2));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Left, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandP2));
		input.AddControllerCommand(static_cast<int>(dae::Controller::AmountOfControllers::One),
			dae::Controller::GamePad::Dpad_Right, dae::ButtonState::Is_Pressed, std::move(moveRightCommandP2));

		// KEYBOARD
		// --------
		std::unique_ptr<dae::MovementCommand> moveUpCommandE{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{0, -1, 0}, 150.f) };
		std::unique_ptr<dae::MovementCommand> moveDownCommandE{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{0, 1, 0}, 150.f) };
		std::unique_ptr<dae::MovementCommand> moveLeftCommandE{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{-1, 0, 0}, 150.f) };
		std::unique_ptr<dae::MovementCommand> moveRightCommandE{ std::make_unique<dae::MovementCommand>(
			player1.get(), glm::vec3{1, 0, 0}, 150.f) };

		input.AddKeyboardCommand(SDL_SCANCODE_W, dae::ButtonState::Is_Pressed, std::move(moveUpCommandE));
		input.AddKeyboardCommand(SDL_SCANCODE_S, dae::ButtonState::Is_Pressed, std::move(moveDownCommandE));
		input.AddKeyboardCommand(SDL_SCANCODE_A, dae::ButtonState::Is_Pressed, std::move(moveLeftCommandE));
		input.AddKeyboardCommand(SDL_SCANCODE_D, dae::ButtonState::Is_Pressed, std::move(moveRightCommandE));

		input.AddKeyboardCommand(SDL_SCANCODE_C, dae::ButtonState::Is_Up, std::make_unique<dae::HealthCommand>(player1.get()));

		input.AddKeyboardCommand(SDL_SCANCODE_Z, dae::ButtonState::Is_Up,
			std::make_unique<dae::ScoreCommand>(player1.get(), scoreIncrementBy10));
		input.AddKeyboardCommand(SDL_SCANCODE_X, dae::ButtonState::Is_Up,
			std::make_unique<dae::ScoreCommand>(player1.get(), scoreIncrementBy100));

		input.AddKeyboardCommand(SDL_SCANCODE_SPACE, dae::ButtonState::Is_Up, std::make_unique<dae::BombCommand>(player1.get()));
		input.AddKeyboardCommand(SDL_SCANCODE_B, dae::ButtonState::Is_Up, std::make_unique<dae::DetonateCommand>(player1.get()));

		bombermanGameScene.Add(std::move(player1));
		bombermanGameScene.Add(std::move(player2));
	}

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
}

int main(int, char* []) 
{
	dae::Minigin engine("../Data/");
	std::unique_ptr<dae::GameStateUpdater> gameStateUpdater{ std::make_unique<dae::GameStateUpdater>() };
	engine.Run(load, gameStateUpdater.get());
	return 0;
}