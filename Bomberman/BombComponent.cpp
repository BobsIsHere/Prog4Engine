#include "AudioServiceLocator.h"
#include "ExplosionComponent.h"
#include "TextureComponent.h"
#include "GameAudioSystem.h"
#include "BombComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include <iostream>

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
	BombTimer();
}

void dae::BombComponent::StartBombTimer() 
{
	m_StartTime = std::chrono::high_resolution_clock::now(); 
	m_IsTimerRunning = true; 
	 
	dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanDropsBomb.wav", 0.5f);
}

void dae::BombComponent::ExplodeBomb()
{
	// Middle Explosion Object
	auto middleExplosionObject = std::make_unique<GameObject>(); 
	middleExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(middleExplosionObject.get()));
	middleExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(middleExplosionObject.get(), 2.f));
	middleExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionMiddle.png");
	middleExplosionObject->SetParent(GetGameObject(), false);

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(middleExplosionObject));

	// Side Explosion Object
	for (int idx = 0; idx < 3; ++idx) 
	{
		auto sideExplosionObject = std::make_unique<GameObject>();
		sideExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(sideExplosionObject.get()));
		sideExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(sideExplosionObject.get(), 2.f));
		sideExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionSide.png");
		sideExplosionObject->SetParent(GetGameObject(), false);

		// Set side explosion position with some offset
		glm::vec3 offset = glm::vec3(idx % 2 == 0 ? -16 : 16, idx / 2 == 0 ? -16 : 16, 0); 
		sideExplosionObject->SetLocalPosition(GetGameObject()->GetLocalPosition() + offset);  

		// Add side explosion object to the scene
		SceneManager::GetInstance().GetActiveScene()->Add(std::move(sideExplosionObject));
	}

	dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanExplosion.wav", 0.75f);

	GetGameObject()->SetParent(nullptr, false);
	GetGameObject()->SetForRemoval();
	std::cout << "Is set for removal bomb" << std::endl;
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
