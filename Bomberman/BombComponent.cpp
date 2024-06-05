#include <iostream>
#include "AudioServiceLocator.h"
#include "ExplosionComponent.h"
#include "TextureComponent.h"
#include "GameAudioSystem.h"
#include "BombComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"

dae::BombComponent::BombComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject },
	m_IsTimerRunning{ false },
	m_StartTime{},
	m_GridSize{ 32 },
	m_BombDuration{ 3.f }  
{
}

dae::BombComponent::~BombComponent()
{
}

void dae::BombComponent::Update()
{
	if (GetGameObject() != nullptr)
	{
		BombTimer();
	}
}

void dae::BombComponent::StartBombTimer() 
{
	m_StartTime = std::chrono::high_resolution_clock::now(); 
	m_IsTimerRunning = true; 
	 
	dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanDropsBomb.wav", 0.5f);
}

void dae::BombComponent::ExplodeBomb()
{
	const float gridSize{ 32.f };   

	// Middle Explosion Object
	auto middleExplosionObject = std::make_unique<GameObject>("Explosion");
	middleExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(middleExplosionObject.get()));
	middleExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(middleExplosionObject.get(), 2.f));
	middleExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionMiddle.png");
	middleExplosionObject->SetLocalPosition(GetGameObject()->GetLocalPosition()); 

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(middleExplosionObject));

	// Side Explosion Object
	for (size_t idx = 0; idx < 4; ++idx)   
	{
		auto sideExplosionObject = std::make_unique<GameObject>("Explosion");
		sideExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(sideExplosionObject.get()));
		sideExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(sideExplosionObject.get(), 2.f));
		sideExplosionObject->SetParent(GetGameObject(), false); 

		float offsetX{}; 
		float offsetY{}; 

		switch (idx)
		{
		// Top
		case 0:
			offsetY = -gridSize;
			sideExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionTop.png");
			break;
		// Right
		case 1:
			offsetX = gridSize;  
			sideExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionRight.png");
			break;
		// Bottom
		case 2:
			offsetY = gridSize; 
			sideExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionBottom.png");
			break;
		// Left
		case 3:
			offsetX = -gridSize; 
			sideExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionLeft.png");
			break;
		}
		
		sideExplosionObject->SetLocalPosition(offsetX, offsetY);   
		std::cout << "Explosion position: " << sideExplosionObject->GetLocalPosition().x << ", " << sideExplosionObject->GetLocalPosition().y << std::endl;   

		// Add side explosion object to the scene
		SceneManager::GetInstance().GetActiveScene()->Add(std::move(sideExplosionObject));
	}

	dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanExplosion.wav", 0.75f);
	
	GetGameObject()->SetParent(nullptr, false);
	GetGameObject()->SetForRemoval();
}

void dae::BombComponent::BombTimer()
{
	if (m_IsTimerRunning)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_StartTime).count();

		if (duration >= m_BombDuration)
		{
			ExplodeBomb();
			m_IsTimerRunning = false;
		}
	}
}
