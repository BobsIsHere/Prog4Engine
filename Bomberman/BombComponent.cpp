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

	// Top Explosion Object
	auto topExplosionObject = std::make_unique<GameObject>("Explosion");
	topExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(topExplosionObject.get()));
	topExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(topExplosionObject.get(), 2.f));
	topExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionTop.png");
	topExplosionObject->SetLocalPosition(GetGameObject()->GetLocalPosition().x, GetGameObject()->GetLocalPosition().y + (-gridSize)); 

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(topExplosionObject));

	// Bottom Explosion Object
	auto bottomExplosionObject = std::make_unique<GameObject>("Explosion");
	bottomExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(bottomExplosionObject.get()));
	bottomExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(bottomExplosionObject.get(), 2.f));
	bottomExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionBottom.png");
	bottomExplosionObject->SetLocalPosition(GetGameObject()->GetLocalPosition().x, GetGameObject()->GetLocalPosition().y + gridSize); 

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(bottomExplosionObject));

	// Right Explosion Object
	auto rightExplosionObject = std::make_unique<GameObject>("Explosion");
	rightExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(rightExplosionObject.get()));
	rightExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(rightExplosionObject.get(), 2.f));
	rightExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionRight.png");
	rightExplosionObject->SetLocalPosition(GetGameObject()->GetLocalPosition().x + gridSize, GetGameObject()->GetLocalPosition().y);

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(rightExplosionObject));

	// Left Explosion Object
	auto leftExplosionObject = std::make_unique<GameObject>("Explosion");
	leftExplosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(leftExplosionObject.get()));
	leftExplosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(leftExplosionObject.get(), 2.f));
	leftExplosionObject->GetComponent<TextureComponent>()->SetTexture("ExplosionLeft.png");
	leftExplosionObject->SetLocalPosition(GetGameObject()->GetLocalPosition().x + (-gridSize), GetGameObject()->GetLocalPosition().y); 

	SceneManager::GetInstance().GetActiveScene()->Add(std::move(leftExplosionObject));

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
